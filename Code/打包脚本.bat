set /p var=�������ļ���
mkdir %VAR%

cd ./%VAR%
cp ../release/*.dll ./
cp ../release/*.exe ./

mkdir Image

cp ../bin/Image/* ./Image/
pwd

rar a -r ../%VAR%.rar 