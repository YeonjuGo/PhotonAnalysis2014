DirFname=$1
fname=$(echo $DirFname | replace "/" " " | awk '{ print $NF }')


cp $DirFname . 
scp $fname nuclear.korea.ac.kr:/home/jazzitup/forestFiles/
rm $fname
