# awk '{print $1;}' ../../mlrule/pup.data.svm |paste  -  pup.data.svm.predict |sort |uniq -c |less -S


awk '{ if($1>0) {print "1";} else if ($1<=0) {print "0";} }' ../../mlrule/pup.data.svm |paste  -  pup.data.svm.predict.result  > result.1
awk '{if($2=="-1") {print $1,$4,"0";} else if($1=="1") {print $1,$3,"1";}}' result.1  > svm.xls
 awk '{if($2=="-1") {print $1,1-$4,"0";} else if($1=="1") {print $1,$3,"1";}}'  crossvalidation_2_13.predict.1 > crossvalidation_2_13.predict.xls
