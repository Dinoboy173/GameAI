@echo off

cd /d %~dp0

git add .

git status

set /p commitMessage="Enter commit message here: "

echo "%commitMessage%"

git commit -m " %commitMessage% "

git pull

git push

exit /b