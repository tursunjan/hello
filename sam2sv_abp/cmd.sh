cd /mnt/sdc/zhangzb/code/sam2sv_abp
date > time
./SAM2SV -i0 -p5 -s15 -m10 ../SAM2SV/data/60x_100.bwa.fmeas.sam > i0p5s15m10_1
date >> time
./SAM2SV -i1 -p5 -s15 -m10 ../SAM2SV/data/60x_100.bwa.fmeas.sam > i1p5s15m10_1
date >> time
awk '{print $1"\t"$2"\t"$3"\t"0"\t"0"\t"$4"\t"$5;}' i0p5s15m10_1 > i0p5s15m10_1_reg
awk '{print $1"\t"$2"\t"$3"\t"$4"\t"$5"\t"0"\t"0;}' i1p5s15m10_1 > i1p5s15m10_1_reg
cat i0p5s15m10_1_reg i1p5s15m10_1_reg > p5s15m10.abp


