/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Animation7_png;
    const int            Animation7_pngSize = 304650;

    extern const char*   Animation6_png;
    const int            Animation6_pngSize = 243236;

    extern const char*   Animation5_png;
    const int            Animation5_pngSize = 314715;

    extern const char*   Animation4_png;
    const int            Animation4_pngSize = 353839;

    extern const char*   Animation3_png;
    const int            Animation3_pngSize = 353936;

    extern const char*   Animation2_png;
    const int            Animation2_pngSize = 407910;

    extern const char*   Animation1_png;
    const int            Animation1_pngSize = 318793;

    extern const char*   PurpleAnimate_png;
    const int            PurpleAnimate_pngSize = 2595297;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
