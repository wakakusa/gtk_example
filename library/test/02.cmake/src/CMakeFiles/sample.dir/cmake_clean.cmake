FILE(REMOVE_RECURSE
  "CMakeFiles/sample.dir/main.c.o"
  "sample.pdb"
  "sample"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/sample.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
