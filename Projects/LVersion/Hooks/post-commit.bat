
SET REPOS=%1
SET REV=%2

# Test
#svnadmin dump %REPOS% -r %REV% --incremental > out.txt

lversion-post-commit.py %REPOS% %REV%
