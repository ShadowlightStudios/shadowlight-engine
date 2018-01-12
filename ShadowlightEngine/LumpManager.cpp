#include "stdafx.h"
#include "LumpManager.h"
#include "ShadowlightEngine.h"

// This function loads a lump file and enters all of the lumps into it
void LumpManager::LoadLumpFile(string filename)
{
	FILE* f;
	Lump* currentParent = NULL;
	bool testInsert;
	// Open the file
	f = fopen(filename.data(), "rb");

	// If the file open failed
	if (!f)
	{
		// Raise an error and exit
		RaiseError("Failed to load file %s", filename.data());
		return;
	}

	Lump newLump;
	char ch;

	ch = 0;

	// Now, let's load some lumps!!!

	while (true)
	{
		// Start with an unnamed lump
		newLump.name = "";

		// Find the lump's name
		while (true)
		{
			// Read a character
			ch = fgetc(f);

			// Append it to the lump name
			if (ch != '\0' && ch != EOF)
			{
				printf("%c", ch);
				newLump.name += ch;
			}
			// But if it's a null or EOF, break
			else
			{
				break;
			}
		}

		// Now: if this string has length 0
		// (An empty string, or a solitary '\0' in the file)
		// We're going to pop up one level in the lump
		// tree as long as the current parent is not null

		if (newLump.name.length() == 0 && currentParent != NULL)
		{
			currentParent = currentParent->parent;
			// Continue onto the next lump
			continue;
		}

		printf("\n");
		
		// Check for EOF and if there is, exit the loop
		if (ch == EOF)
			break;

		// Now, we have the lump's name

		// Let's read the contentType:
		fread((void*)&newLump.contentType, sizeof(uint16_t), 1, f);

		printf("%d %04x\n", (signed int) newLump.contentType, newLump.contentType);

		// Now, let's read the JSON-formatted metadata
		
		newLump.metadata = "";

		while (true)
		{
			// Read a character
			ch = fgetc(f);

			// Append it to the lump name
			if (ch != '\0' && ch != EOF)
			{
				printf("%c", ch);
				newLump.metadata += ch;
			}
			// But if it's a null or EOF, break
			else
			{
				break;
			}
		}

		printf("\n");

		// Check for EOF and if there is, exit the loop
		if (ch == EOF)
			break;

		// Set loaded and index to blank
		newLump.index = -1;
		newLump.loaded = false;
	
		// Set the parent
		newLump.parent = currentParent;

		// Now we have our loaded lump!
		// Finally, enter into the tree.
		if (currentParent != NULL)
		{
			testInsert = currentParent->Insert(newLump);
		}
		else
		{
			testInsert = this->EnterLump(newLump);
		}
		
		// Do a bit of error checking to see if this lump already existed
		if (!testInsert)
		{
			// Raise an error and exit
			RaiseError("Repeat lump name %s in lump file", newLump.name.data());
			return;
		}

		// Go one level deeper, set the current parent
		currentParent = &newLump;
	}

	// Close the file and exit
	fclose(f);
	return;
}

// Finds a sublump or lump within the lump tree
Lump* LumpManager::FindLump(const Lump& root, string name) const
{
	// Let's start by attempting to find it as a sublump
	const Lump* ptr = &root;

	// Map iterator
	map<string, Lump>::const_iterator iter;

	// eND oF sTRING
	bool eos = false;

	// Markers in the string
	int begin = 0;
	int end = 0;

	// Start the search:
	while (!eos && ptr)
	{
		// Find the first dot (.)
		// If we find a non-underscore or alphanumeric character,
		// raise an error
		end = begin;
		while (true)
		{
			end++;

			// If we've hit the end, break while setting the end of string
			if (end >= name.length())
			{
				eos = true;
				break;
			}

			// Break if we've hit a '.'
			if (name[end] == '.')
			{
				// Break;  we've found this name
				break;
			}

			if (name[end] != '_' && !isalnum(name[end]))
			{
				// Raise an error, return
				RaiseError("Invalid lump directory \"%s\"", name.data());
				return NULL;
			}
		}

		// Navigate the tree
		string toNavigate(name.substr(begin, end - begin));
		iter = ptr->subLumps.find(toNavigate);
		// Make sure that we actually found it
		if (iter == ptr->subLumps.end())
		{
			ptr = NULL;
			break;
		}
		ptr = &(iter->second);

		// Set the start as the end past the dot for the next round
		begin = end + 2;
	}

	// If we've come this far with a valid pointer, we can return it
	if(ptr) return (Lump*) ptr;
	
	// But otherwise, we're going to need to do some more searching
	return this->FindLump(name);
}

Lump* LumpManager::FindLump(string name) const
{
	// Let's start by attempting to find it as a sublump
	const Lump* ptr = NULL;

	// Map iterator
	map<string, Lump>::const_iterator iter;

	// eND oF sTRING
	bool eos = false;

	// Markers in the string
	int begin = 0;
	int end = 0;

	// Start the search:
	while (!eos)
	{
		// Find the first dot (.)
		// If we find a non-underscore or alphanumeric character,
		// raise an error
		end = begin;
		while (true)
		{
			end++;

			// If we've hit the end, break while setting the end of string
			if (end >= name.length())
			{
				eos = true;
				break;
			}

			// Break if we've hit a '.'
			if (name[end] == '.')
			{
				// Break;  we've found this name
				break;
			}

			if (name[end] != '_' && !isalnum(name[end]))
			{
				// Raise an error, return
				RaiseError("Invalid lump directory \"%s\"", name.data());
				return NULL;
			}
		}

		// Navigate the tree
		string toNavigate(name.substr(begin, end - begin));
		if (ptr)
		{
			iter = ptr->subLumps.find(toNavigate);
			// If we've hit a dead end, exit with a NULL pointer
			if (iter == ptr->subLumps.end())
			{
				ptr = NULL;
				break;
			}
		}
		else
		{
			iter = lumps.find(toNavigate);
			// If we've hit a dead end, exit with a NULL pointer
			if (iter == lumps.end())
			{
				break;
			}
		}
		// Navigate the tree
		ptr = &(iter->second);

		// Set the start as the end past the dot for the next round
		begin = end + 2;
	}
	// Let's return whatever we have now
	return (Lump*)ptr;
}

// Loads a lump that has been iniatialized with metadata, name, and type,
// this function returns it's index
int LumpManager::LoadLump(Lump& in)
{
	// First, let's make sure that it's not already loaded
	if (in.loaded) return in.index;

	// Let's figure out which Manager it's from
	Manager* man = this->ManagerFromLumpType(in);

	// Make sure that we have a valid Manager
	if (!man)
	{
		// If not, exit with an error
		RaiseError("Lump %s doesn\'t have a valid Manager", in.name.data());
		return -1;
	}

	// Let's load it!
	in.index = man->Create(in);

	// If we've failed to load for some reason, exit with an error and a -1
	if (in.index == -1)
	{
		RaiseError("Failed to load lump %s", in.name.data());
		return -1;
	}

	// Now, do a recursive loading of the sub-lumps
	for (map<string, Lump>::iterator iter = in.subLumps.begin();
		iter != in.subLumps.end();
		++iter)
	{
		LoadLump(iter->second);
	}

	// We've loaded!
	in.loaded = true;

	// Otherwise, we're done!
	// Exit with the index
	cout << "Loaded lump " << in.name << " with index " << in.index << endl;
	return in.index;
}

// Just exits; nothing to do
void LumpManager::Cleanup()
{
	return;
}

// Enter a lump into the base
bool LumpManager::EnterLump(const Lump& lumpIn)
{
	// If the key does not exist, carry on
	if (lumps.find(lumpIn.name) == lumps.end())
	{
		lumps.insert(make_pair(lumpIn.name, lumpIn));
		return true;
	}
	// Otherwise, this lump already exists, and we can exit with false
	else
		return false;
}

Manager* LumpManager::ManagerFromLumpType(const Lump& in) const
{
	// Let's do a switch on the type to get the right manager for it
	switch (in.contentType)
	{
	case LT_EMPTY:
		return NULL;
	case LT_VERTEX_SHADER:
	case LT_FRAGMENT_SHADER:
	case LT_GEOMETRY_SHADER:
	case LT_PROGRAM:
		return (Manager*)pEngine->shaderManager;
	case LT_TEXTURE_1D:
	case LT_TEXTURE_1D_ARRAY:
	case LT_TEXTURE_2D:
	case LT_TEXTURE_2D_ARRAY:
	case LT_TEXTURE_2D_MULTISAMPLE:
	case LT_TEXTURE_2D_MULTISAMPLE_ARRAY:
	case LT_TEXTURE_3D:
	case LT_TEXTURE_CUBE:
	case LT_TEXTURE_CUBE_ARRAY:
	case LT_TEXTURE_RECT:
		return (Manager*)pEngine->textureManager;
	case LT_SOUND:
	case LT_MUSIC_OGG:
	case LT_MUSIC_MP3:
		return (Manager*) pEngine->soundManager;
	case LT_TEXT:
	case LT_INPUT_BINDINGS:
	case LT_MAP:
	case LT_TRANSFORM_FEEDBACK_BUFFER:
	case LT_UNIFORM:
	case LT_VERTEX_ARRAY:
	default:
	{
		RaiseError("Unrecognized lump type in lump %s", in.name.data());
		break;
	}
	}
	return NULL;
}

// Simply cleanup
LumpManager::~LumpManager()
{
	Cleanup();
}
