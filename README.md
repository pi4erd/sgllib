# sgllib

A submodule library for OpenGL for a quick startup.

I made this for my projects but you may use it as licensed by [LICENSE](https://github.com/pi4erd/sgllib/blob/main/LICENSE)

## How to use

**IMPORTANT!** You have to use CMake for seemless integration :)

In an existing git repository, make a submodule:

```bash
git submodule add https://github.com/pi4erd/sgllib.git
```

Then add submodule folder to CMakeLists.txt as a subdirectory.

```cmake
add_subdirectory(sgllib)
```

You should then have access to 2 libraries (also defined by `${SGL_LIBRARIES}`): sgl, sglad.
You can just link them like normal.

Include directories are defined by `${SGL_INCLUDE_DIRECTORIES}`.

Next follow [documentation](https://www.youtube.com/watch?v=dQw4w9WgXcQ) (that we don't have at the moment: TODO)

## Contribute

Please help me with issues you encounter. I am fixing this only if I personally encounter issues.
If anyone else is using this library, I would be glad to help them and fix their issues :)
