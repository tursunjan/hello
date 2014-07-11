cd /home/user/workspace/libsvm-3.17/tools 
head -521 ../../mlrule/pup.data.svm > 1.svm
head -1042 ../../mlrule/pup.data.svm > 2
tail -521 2 > 2.svm
head -1563 ../../mlrule/pup.data.svm > 3
tail -521 3 > 3.svm
head -2084 ../../mlrule/pup.data.svm > 4
tail -521 4 > 4.svm
head -2605 ../../mlrule/pup.data.svm > 5
tail -521 5 > 5.svm
head -3126 ../../mlrule/pup.data.svm > 6
tail -521 6 > 6.svm
head -3647 ../../mlrule/pup.data.svm > 7
tail -521 7 > 7.svm
head -4168 ../../mlrule/pup.data.svm > 8
tail -521 8 > 8.svm
head -4689 ../../mlrule/pup.data.svm > 9
tail -521 9 > 9.svm
tail -526 ../../mlrule/pup.data.svm  > 10.svm


cat 2.svm 3.svm 4.svm 5.svm 6.svm 7.svm 8.svm 9.svm 10.svm > test1.svm
cat 1.svm 3.svm 4.svm 5.svm 6.svm 7.svm 8.svm 9.svm 10.svm > test2.svm
cat 1.svm 2.svm 4.svm 5.svm 6.svm 7.svm 8.svm 9.svm 10.svm > test3.svm
cat 1.svm 2.svm 3.svm 5.svm 6.svm 7.svm 8.svm 9.svm 10.svm > test4.svm
cat 1.svm 2.svm 3.svm 4.svm 6.svm 7.svm 8.svm 9.svm 10.svm > test5.svm
cat 1.svm 2.svm 3.svm 4.svm 5.svm 7.svm 8.svm 9.svm 10.svm > test6.svm
cat 1.svm 2.svm 3.svm 4.svm 5.svm 6.svm 8.svm 9.svm 10.svm > test7.svm
cat 1.svm 2.svm 3.svm 4.svm 5.svm 6.svm 7.svm 9.svm 10.svm > test8.svm
cat 1.svm 2.svm 3.svm 4.svm 5.svm 6.svm 7.svm 8.svm 10.svm > test9.svm
cat 1.svm 2.svm 3.svm 4.svm 5.svm 6.svm 7.svm 8.svm 9.svm  > test10.svm

/home/user/workspace/libsvm-3.17/tools/easy.py test1.svm 1.svm
/home/user/workspace/libsvm-3.17/tools/easy.py test2.svm 2.svm
/home/user/workspace/libsvm-3.17/tools/easy.py test3.svm 3.svm
/home/user/workspace/libsvm-3.17/tools/easy.py test4.svm 4.svm
/home/user/workspace/libsvm-3.17/tools/easy.py test5.svm 5.svm
/home/user/workspace/libsvm-3.17/tools/easy.py test6.svm 6.svm
/home/user/workspace/libsvm-3.17/tools/easy.py test7.svm 7.svm
/home/user/workspace/libsvm-3.17/tools/easy.py test8.svm 8.svm
/home/user/workspace/libsvm-3.17/tools/easy.py test9.svm 9.svm
/home/user/workspace/libsvm-3.17/tools/easy.py test10.svm 10.svm

