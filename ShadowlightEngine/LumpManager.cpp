#include "stdafx.h"
#include "LumpManager.h"

// Just kinda sets everything up
LumpManager::LumpManager(ShadowlightEngine* gamePointer)
{
	game = gamePointer;

	root = (LumpNode*)0;
	shm = (ShaderManager*)0;
	depth = 0;
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
		RaiseError(FILE_LOAD_FAIL);
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
		// Finally, enter into the tree.
		EnterLump(&newLump);

		break;
	}

	// Close the file and exit
	fclose(f);
	return;
}

// Recursive function that deletes a tree
void LumpManager::DeleteTree(LumpNode* tree)
{
	// If this node exists
	if (tree)
	{
		// Delete it's branches
		DeleteTree(tree->left);
		DeleteTree(tree->right);
		// Delete itself
		delete tree;
	}
}

// Find a lump inside the tree
LumpNode* LumpManager::GetLumpAddress(string name)
{
	// Start with the root node
	LumpNode* ptr = root;
	int compar;
	// Loop until we find it
	while (true)
	{
		// If this ptr is null, return null
		if (!ptr)
			return 0;
		// Otherwise, compare this node's name with the name input
		compar = ptr->content.name.compare(name);
		// If it's larger, navigate right
		if (compar > 0)
		{
			ptr = ptr->right;
		}
		// If it's smaller, navigate left
		else if (compar < 0)
		{
			ptr = ptr->left;
		}
		// If it's the same, we've found it
		else
		{
			return ptr;
		}
	}
}

// Deletes tree, sets depth to 0
void LumpManager::Cleanup()
{
	depth = 0;
	DeleteTree(root);
}

// Set a shader manager
void LumpManager::SetShaderManager(ShaderManager* ptr)
{
	shm = ptr;
}

// Enter a lump into the tree
void LumpManager::EnterLump(Lump* in)
{
	// Start searching with the root node
	LumpNode* ptr = root;
	int compar;
	// If the tree is empty, just skip the next part after allocatating a new branch
	if (!ptr)
	{
		ptr = new LumpNode;
		// Set blank pointers
		ptr->left = 0;
		ptr->right = 0;
		root = ptr;
	}
	else
	{
		// Loop until we find a free branch
		while (true)
		{
			// Compare this node's name with the name input
			compar = ptr->content.name.compare(in->name);
			// If it's larger, navigate right
			if (compar > 0)
			{
				// If we've found an open spot
				if (!ptr->right)
				{
					// Allocate a new lump node
					ptr->right = new LumpNode;
					ptr = ptr->right;
					// Set blank pointers
					ptr->left = 0;
					ptr->right = 0;
					break;
				}
				else
				{
					// Otherwise, just navigate right
					ptr = ptr->right;
				}
			}
			// If it's smaller, navigate left
			else if (compar < 0)
			{
				// If we've found an open spot
				if (!ptr->left)
				{
					// Allocate a new lump node
					ptr->left = new LumpNode;
					ptr = ptr->left;
					// Set blank pointers
					ptr->left = 0;
					ptr->right = 0;
					break;
				}
				else
				{
					// Otherwise, just navigate left
					ptr = ptr->left;
				}
			}
			// If it's the same, we've found it
			else
			{
				// Just overwrite the existing one
				break;
			}
		}
	}
	// Now that we have a pointer to a new (or old) lump, just set the lump and do the preliminary loading
	ptr->content = *in;
	// Let's do a switch on the type to load it appropiately
	switch (ptr->content.contentType)
	{
	case LT_EMPTY:
	{
		printf("No lump");
		break;
	}
	case LT_VERTEX_SHADER:
	case LT_FRAGMENT_SHADER:
	case LT_GEOMETRY_SHADER:
	{
		printf("Shader");
		if (shm != 0)
		{
			ptr->content.index = shm->CreateShader();
		}
		break;
	}
	case LT_PROGRAM:
	{
		printf("Shader program");
		break;
	}
	case LT_UNIFORM:
	{
		printf("Uniform list");
		break;
	}
	case LT_VERTEX_ARRAY:
	{
		printf("Vertex array");
		break;
	}
	case LT_TEXTURE_1D:
	{
		printf("1D texture");
		break;
	}
	case LT_TEXTURE_1D_ARRAY:
	{
		printf("1D texture array");
		break;
	}
	case LT_TEXTURE_2D:
	{
		printf("2D texture");
		break;
	}
	case LT_TEXTURE_2D_ARRAY:
	{
		printf("2D texture array");
		break;
	}
	case LT_TEXTURE_2D_MULTISAMPLE:
	{
		printf("2D multisampled texture");
		break;
	}
	case LT_TEXTURE_2D_MULTISAMPLE_ARRAY:
	{
		printf("2D multisampled texture array");
		break;
	}
	case LT_TEXTURE_3D:
	{
		printf("3D texture");
		break;
	}
	case LT_TEXTURE_CUBE:
	{
		printf("Cube map texture");
		break;
	}
	case LT_TEXTURE_CUBE_ARRAY:
	{
		printf("Cube map texture array");
		break;
	}
	case LT_TEXTURE_RECT:
	{
		printf("Rectangle texture");
		break;
	}
	case LT_SOUND:
	{
		printf("PCM sound");
		break;
	}
	case LT_MUSIC_OGG:
	{
		printf("OGG music");
		break;
	}
	case LT_MUSIC_MP3:
	{
		printf("MP3 music");
		break;
	}
	case LT_TEXT:
	{
		printf("Text");
		break;
	}
	case LT_INPUT_BINDINGS:
	{
		printf("Input binding");
		break;
	}
	case LT_MAP:
	{
		printf("Map");
		break;
	}
	case LT_TRANSFORM_FEEDBACK_BUFFER:
	{
		printf("Transform feeback buffer");
		break;
	}
	default:
	{
		RaiseError(LUMP_TYPE_ERROR);
		break;
	}
	}
	printf(" lump \"%s\"\n", ptr->content.name.data());
	return;
}

// Simply cleanup
LumpManager::~LumpManager()
{
	Cleanup();
}
