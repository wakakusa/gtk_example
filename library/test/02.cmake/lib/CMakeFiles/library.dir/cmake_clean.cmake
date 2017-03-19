FILE(REMOVE_RECURSE
  "CMakeFiles/library.dir/library.c.o"
  "liblibrary.pdb"
  "liblibrary.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/library.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
