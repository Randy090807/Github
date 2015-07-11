set /p var=请输入文件名
mkdir %VAR%

cd ./%VAR%
cp ../release/*.dll ./
cp ../release/*.exe ./

mkdir Image

cp ../bin/Image/* ./Image/
pwd

rar a -r ../%VAR%.rar 