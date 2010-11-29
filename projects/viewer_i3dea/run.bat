@echo 

@echo "Changing current directory to the directory where the bat file exists..."
for /f %%i in ("%0") do set curpath=%%~dpi
cd /d %curpath% 
ViewerI3dea.exe %*

