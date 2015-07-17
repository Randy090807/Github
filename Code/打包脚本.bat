set /p var=请输入文件名
mkdir %VAR%

cd ./%VAR%
cp ../release/*.dll ./
cp ../release/*.exe ./

mkdir Image
mkdir Data
mkdir Log

cp ../bin/Image/* ./Image/
cp ../bin/Data/* ./Data/
pwd

rar a -r ../%VAR%.rar 