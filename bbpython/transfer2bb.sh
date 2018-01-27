
cd .. 
echo compressing File
tar -czvf bbpython.tar.gz /home/steve/project/brickHack/EVT_Brickhack18/bbpython
echo starting transfer
sudo scp bbpython.tar.gz  debian@192.168.7.2:/home/debian/BB_BrickHack 

