#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"s test_0_grep.txt VAR"
"for s21_grep.c s21_grep.h Makefile VAR"
"for s21_grep.c VAR"
"-e for -e ^int s21_grep.c s21_grep.h Makefile VAR"
"-e for -e ^int s21_grep.c VAR"
"-e regex -e ^print s21_grep.c VAR -f test_ptrn_grep.txt"
"-e while -e void s21_grep.c Makefile VAR -f test_ptrn_grep.txt"
)

declare -a extra=(
"-n -e ^\} test_1_grep.txt"
"-ce ^int test_1_grep.txt test_2_grep.txt"
"-e ^int test_1_grep.txt"
"-nivh = test_1_grep.txt test_2_grep.txt"
"-e"
"-noe ing -e as -e the -e not -e is -e visit test_6_grep.txt"
"-ie INT test_5_grep.txt"
"-ne = -e out test_5_grep.txt"
"-iv int test_5_grep.txt"
"-in int test_5_grep.txt"
"-c -l aboba test_1_grep.txt test_5_grep.txt"
"-v test_1_grep.txt -e ank"
"-noe ) test_5_grep.txt"
"-l for test_1_grep.txt test_2_grep.txt"
"-o -e int test_4_grep.txt"
"-e = -e out test_5_grep.txt"
"-c -e . test_1_grep.txt -e '.'"
"-l for no_file.txt test_2_grep.txt"
"-f test_3_grep.txt test_5_grep.txt"
)

#testing()
#{
#    t=$(echo "$@" | sed "s/VAR/$var/")
#    ./s21_grep $t > my_grep_func_test.log
#    grep $t > grep_func.log
#    DIFF_RES="$(diff -s my_grep_func_test.log grep_func.log)"
#    (( COUNTER++ ))
#    if [ "$DIFF_RES" == "Files my_grep_func_test.log and grep_func.log are identical" ]
#    then
#      (( SUCCESS++ ))
#      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
#    else
#      (( FAIL++ ))
#      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"
#    fi
#    rm -f my_grep_func_test.log grep_func.log
#}

#echo "" > log.txt
#
#for var in -v -c -l -n -h -o
#do
#  for var2 in -v -c -l -n -h -o
#  do
#      for var3 in -v -c -l -n -h -o
#      do
#        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
#        then
#          TEST1="for s21_grep.c s21_grep.h Makefile $var $var2 $var3"
#          echo "$TEST1"
#          ./s21_grep $TEST1 > s21_grep.txt
#          grep $TEST1 > grep.txt
#          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#          (( COUNTER++ ))
#          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#            then
#              (( SUCCESS++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST1"
#            else
#              echo "$TEST1" >> log.txt
#              (( FAIL++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST1"
#          fi
#          rm s21_grep.txt grep.txt
#
#          TEST2="for s21_grep.c $var $var2 $var3"
#          echo "$TEST2"
#          ./s21_grep $TEST2 > s21_grep.txt
#          grep $TEST2 > grep.txt
#          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#          (( COUNTER++ ))
#          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#            then
#              (( SUCCESS++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST2"
#            else
#              echo "$TEST2" >> log.txt
#              (( FAIL++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST2"
#          fi
#          rm s21_grep.txt grep.txt
#
#          TEST3="-e for -e ^int s21_grep.c s21_grep.h Makefile $var $var2 $var3"
#          echo "$TEST3"
#          ./s21_grep $TEST3 > s21_grep.txt
#          grep $TEST3 > grep.txt
#          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#          (( COUNTER++ ))
#          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#            then
#              (( SUCCESS++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST3"
#            else
#              echo "$TEST3" >> log.txt
#              (( FAIL++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST3"
#          fi
#          rm s21_grep.txt grep.txt
#
#          TEST4="-e for -e ^int s21_grep.c $var $var2 $var3"
#          echo "$TEST4"
#          ./s21_grep $TEST4 > s21_grep.txt
#          grep $TEST4 > grep.txt
#          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#          (( COUNTER++ ))
#          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#            then
#              (( SUCCESS++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST4"
#            else
#              echo "$TEST4" >> log.txt
#              (( FAIL++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST4"
#          fi
#          rm s21_grep.txt grep.txt
#
#          TEST5="-e regex -e ^print s21_grep.c $var $var2 $var3 -f pattern.txt"
#          echo "$TEST5"
#          ./s21_grep $TEST5 > s21_grep.txt
#          grep $TEST5 > grep.txt
#          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#          (( COUNTER++ ))
#          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#            then
#              (( SUCCESS++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST5"
#            else
#              echo "$TEST5" >> log.txt
#              (( FAIL++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST5"
#          fi
#          rm s21_grep.txt grep.txt
#
#          TEST6="-e while -e void s21_grep.c Makefile $var $var2 $var3 -f pattern.txt"
#          echo "$TEST6"
#          ./s21_grep $TEST6 > s21_grep.txt
#          grep $TEST6 > grep.txt
#          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#          (( COUNTER++ ))
#          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#            then
#              (( SUCCESS++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST6"
#            else
#              echo "$TEST6" >> log.txt
#              (( FAIL++ ))
#              echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $TEST6"
#          fi
#          rm s21_grep.txt grep.txt
#
#        fi
#      done
#  done
#done
#
#for i in "${extra[@]}"
#do
#    var="-"
#    testing $i
#done

## 1 параметр
#for var1 in v c l n h o
#do
#    for i in "${tests[@]}"
#    do
#        var="-$var1"
#        testing $i
#    done
#done

## 2 параметра
#for var1 in v c l n h o
#do
#    for var2 in v c l n h o
#    do
#        if [ $var1 != $var2 ]
#        then
#            for i in "${tests[@]}"
#            do
#                var="-$var1 -$var2"
#                testing $i
#            done
#        fi
#    done
#done
#
## 3 параметра
#for var1 in v c l n h o
#do
#    for var2 in v c l n h o
#    do
#        for var3 in v c l n h o
#        do
#            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
#            then
#                for i in "${tests[@]}"
#                do
#                    var="-$var1 -$var2 -$var3"
#                    testing $i
#                done
#            fi
#        done
#    done
#done
#
## 2 сдвоенных параметра
#for var1 in v c l n h o
#do
#    for var2 in v c l n h o
#    do
#        if [ $var1 != $var2 ]
#        then
#            for i in "${tests[@]}"
#            do
#                var="-$var1$var2"
#                testing $i
#            done
#        fi
#    done
#done
#
## 3 строенных параметра
#for var1 in v c l n h o
#do
#    for var2 in v c l n h o
#    do
#        for var3 in v c l n h o
#        do
#            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
#            then
#                for i in "${tests[@]}"
#                do
#                    var="-$var1$var2$var3"
#                    testing $i
#                done
#            fi
#        done
#    done
#done

echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"

if [ "$FAIL" -ne "0" ]
then
  exit 1
fi