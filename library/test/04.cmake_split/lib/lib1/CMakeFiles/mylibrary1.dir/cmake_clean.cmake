FILE(REMOVE_RECURSE
  "CMakeFiles/mylibrary1.dir/library1.c.o"
  "libmylibrary1.pdb"
  "libmylibrary1.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/mylibrary1.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
