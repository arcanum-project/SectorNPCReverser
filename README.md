# Description

Parse Arcanum's global map and identify which .bmp file to use for NPCs.

Currently only works for crash site sector.

Results of parsing are stored to json file with the following structure:

```
{
  "npcs": [
    {
      "tileInstanceId": 2984, // defines a tile where the NPC is located. Works similarly to WorldEd where tiles stored as contiguous columns. 0 - first row, first column; 64 - first row, second column, etc.
      "textureName": "efmcdxaa", // name of bmp file to use
    }
  ]
}
```

Input and output file paths are currently hardcoded.
