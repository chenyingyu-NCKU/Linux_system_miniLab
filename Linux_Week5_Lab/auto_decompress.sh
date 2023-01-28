
#### examine ####

# 增新missing_list 以及wrong_list
cd /home/f74096247/Linux_Week5_Lab
touch missing_list.txt
touch wrong_list.txt

# 找出錯誤、沒繳交的
# student_id 中是一行一行的，每讀到一個就去compressed file中確認
while read STD_ID
 do
   FILE=$(find /home/f74096247/Linux_Week5_Lab/compressed_files -name ${STD_ID}.zip -o -name ${STD_ID}.tar.gz -o -name ${STD_ID}.rar -o -name ${STD_ID}.dika)
   LEGAL=$(find /home/f74096247/Linux_Week5_Lab/compressed_files -name ${STD_ID}.zip -o -name ${STD_ID}.tar.gz -o -name ${STD_ID}.rar)
 
   # 表示沒有找到對應的壓縮檔，記錄在 missing
   if [ !-e ${FILE}];
   then
     echo ${STD_ID} >> "/home/f74096247/Linux_Week5_Lab/missing_list.txt"
     
   # 找到對應的 dika，記錄在 wrong  
   elif [ !-e ${LEGAL}];
   then
     echo ${STD_ID} >> "/home/f74096247/Linux_Week5_Lab/wrong_list.txt"
   fi 
 
done < "./student_id"


#### classify ####

# 跑到compressed_file中新建四個資料夾
for dir in /home/f74096247/Linux_Week5_Lab/compressed_files;
do
mkdir "$dir"/zip;
mkdir "$dir"/rar;
mkdir "$dir"/tar.gz;
mkdir "$dir"/unknown;
done
 
# 分類
cd /home/f74096247/Linux_Week5_Lab/compressed_files/$1
 
mv *.zip /home/f74096247/Linux_Week5_Lab/compressed_files/$1/zip
mv *.tar.gz /home/f74096247/Linux_Week5_Lab/compressed_files/$1/tar.gz
mv *.rar /home/f74096247/Linux_Week5_Lab/compressed_files/$1/rar
mv *.dika /home/f74096247/Linux_Week5_Lab/compressed_files/$1/unknown



#### 解壓縮 ####

cd /home/f74096247/Linux_Week5_Lab/compressed_files/zip
for file in *.zip;
do
unzip "${file}";
done
 
cd /home/f74096247/Linux_Week5_Lab/compressed_files/rar
for f in *.rar;
do
unrar e "${f}";
done
 
cd /home/f74096247/Linux_Week5_Lab/compressed_files/tar.gz
for ARK in ./*.tar.gz;
do
tar xvf "$ARK";
done


