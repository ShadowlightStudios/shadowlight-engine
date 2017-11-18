#include "stdafx.h"
#include "LumpManager.h"

void LumpManager::RegisterWithEngine(ShadowlightEngine * pEngine) //for use with/after default constructor initialization
{
	game = pEngine;

	root = (LumpNode*)0;
	shm = (ShaderManager*)0;
	depth = 0;
}

// Just kinda sets everything up
LumpManager::LumpManager(ShadowlightEngine* gamePointer)
{
	game = gamePointer;
<<<<<<< HEAD
=======

	root = (LumpNode*)0;
	shm = (ShaderManager*)0;
	depth = 0;
}

LumpManager::LumpManager()
{
}

// Recursive function that prints the lump tree
void LumpManager::RecursivePrintTree(LumpNode* in)
{
	if (in != 0)
	{
		// Print the tree to the right
		RecursivePrintTree(in->right);
		// Print this node
		printf("Type:\t%04x\tName:\t%s\n", in->content.contentType, in->content.name.data());
		// Print the tree to the left
		RecursivePrintTree(in->left);
	}
}

// Print the lump tree
void LumpManager::PrintTree()
{
	// Just call the recursive function
	RecursivePrintTree(root);
>>>>>>> pr/2
}

// This function loads a lump file and enters all of the lumps into it
void LumpManager::LoadLumpFile(string filename)
{
	FILE* f;
	// Open the file
	f = fopen(filename.data(), "rb");

	// If the file open failed
	if (f == 0)
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
		// tree

		if (newLump.name.length() == 0)
		{
			// TO BE CONTINUED . . .
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

		// Now we have our loaded lump!
	}

	// Close the file and exit
	fclose(f);
	return;
}

// Does nothing
void LumpManager::Cleanup()
{
	return;
}

bool LumpManager::LoadLump(LuaLump* lumpIn)
{
	// First, check if this lump is already loaded or not
	if (lumpIn->loaded)
		return true;
	switch (lumpIn->contentType)
	{
	case LT_EMPTY:
		return true;
	case LT_VERTEX_SHADER:
	{
		printf("Vertex shader\n");
		break;
	}
	}
	return false;
}

// Simply cleanup
LumpManager::~LumpManager()
{
	Cleanup();
}
