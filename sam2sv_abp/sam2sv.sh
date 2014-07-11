cd /mnt/sdc/zhangzb/code/sam2sv_abp
./SAM2SV -i0 -p5 -s15 -m10 ../SAM2SV/data/60x_100.bwa.fmeas.sam > i0p5s15m10
./SAM2SV -i1 -p5 -s15 -m10 ../SAM2SV/data/60x_100.bwa.fmeas.sam > i1p5s15m10 

cat i0p5s15m10 i1p5s15m10  > p5s15m10


