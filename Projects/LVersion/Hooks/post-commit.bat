
SET REPOS=%1
SET REV=%2
SET DIR=%REPOS%//hooks

REM Test
REM svnadmin dump %REPOS% -r %REV% --incremental > out.txt

python %DIR%//lversion-post-commit.py %REPOS% %REV%
