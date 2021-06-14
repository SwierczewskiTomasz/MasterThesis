#!/bin/bash
tests=0
valgrind=0

while test $# -gt 0; do
  case $1 in
    -t|--tests)
      tests=1
      shift
      ;;
    -v|--valgrind)
      valgrind=1
      shift
      ;;
    *)
      break
      ;;
  esac
done

if [ $tests == 1 ];
then
    make test
    build/DTFE
elif [ $valgrind == 1 ];
then
    make main
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose build/DTFE --input ../data/odPanaProfHellwinga/ELEPHANT_GR_R1_out38_f0.001.ascii --output ../wyniki/DTFE_test_2_2021_05_06_128_1.a_den --grid 128 --PHgrid 32 --region 0 1 0 1 0 1 --massInSuperpoints 7.798537 --monteCarlo --nMonteCarlo 10 --onlyDT &> out/valgrind2.txt
else
    make main
    build/DTFE --saveFileType 0 --input ../data/odPanaProfHellwinga/ELEPHANT_GR_R1_out38_f0.001.ascii --output ../wyniki/DTFE_test_2_2021_06_14_32_2.a_den --grid 128 --PHgrid 64 --region 0 1 0 1 0 1 --massInSuperpoints 7.798537 --nMonteCarlo 100 --monteCarlo #--points 100000
fi