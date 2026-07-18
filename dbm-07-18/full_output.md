

tribeirinho@GAMEON-PC:~/42/Milestone03/Codexion$ make test_many
# Testing Errors
## Testing NULL

valgrind --tool=helgrind ./Codexion 2> dbm/debugging_NULL.txt


Incorrect argument input.
Usage: ./Codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
make: [Makefile:103: test_many] Error 254 (ignored)

## Testing with 1 Coder

valgrind --tool=helgrind ./Codexion 1 1000 200 200 200 3 100 fifo 2> dbm/debugging_one.txt


1005 1 burned out

# Testing 2

## Testing with 2 Coders, no Burnout FIFO

valgrind --tool=helgrind ./Codexion 2 8000 200 200 200 3 100 fifo 2> dbm/debugging_2sf.txt


23 1 has taken a dongle
26 1 has taken a dongle
27 1 is compiling
231 1 is debugging
337 2 has taken a dongle
338 2 has taken a dongle
339 2 is compiling
433 1 is refactoring
543 2 is debugging
649 1 has taken a dongle
650 1 has taken a dongle
651 1 is compiling
744 2 is refactoring
854 1 is debugging
956 2 has taken a dongle
957 2 has taken a dongle
957 2 is compiling
1054 1 is refactoring
1160 2 is debugging
1262 1 has taken a dongle
1264 1 has taken a dongle
1265 1 is compiling
1361 2 is refactoring
1571 2 has taken a dongle
1571 2 has taken a dongle
1572 2 is compiling

## Testing with 2 Coders, no Burnout EDF

valgrind --tool=helgrind ./Codexion 2 8000 200 200 200 3 100 edf 2> dbm/debugging_2se.txt


25 1 has taken a dongle
27 1 has taken a dongle
29 1 is compiling
233 1 is debugging
339 2 has taken a dongle
339 2 has taken a dongle
340 2 is compiling
435 1 is refactoring
543 2 is debugging
647 1 has taken a dongle
648 1 has taken a dongle
649 1 is compiling
744 2 is refactoring
852 1 is debugging
956 2 has taken a dongle
958 2 has taken a dongle
958 2 is compiling
1052 1 is refactoring
1161 2 is debugging
1264 1 has taken a dongle
1264 1 has taken a dongle
1265 1 is compiling
1362 2 is refactoring
1573 2 has taken a dongle
1573 2 has taken a dongle
1574 2 is compiling

## Testing with 2 Coders, no Burnout FIFO, long cooldown

valgrind --tool=helgrind ./Codexion 2 8000 200 200 200 3 1000 fifo 2> dbm/debugging_2lf.txt


27 1 has taken a dongle
29 1 has taken a dongle
31 1 is compiling
238 1 is debugging
441 1 is refactoring
1243 2 has taken a dongle
1243 2 has taken a dongle
1244 2 is compiling
1448 2 is debugging
1649 2 is refactoring
2454 1 has taken a dongle
2456 1 has taken a dongle
2457 1 is compiling
2661 1 is debugging
2862 1 is refactoring
3663 2 has taken a dongle
3664 2 has taken a dongle
3665 2 is compiling
3869 2 is debugging
4069 2 is refactoring
4873 1 has taken a dongle
4873 1 has taken a dongle
4875 1 is compiling
6083 2 has taken a dongle
6084 2 has taken a dongle
6085 2 is compiling

## Testing with 2 Coders, no Burnout EDF, long cooldown

valgrind --tool=helgrind ./Codexion 2 8000 200 200 200 3 1000 edf 2> dbm/debugging_2le.txt


20 1 has taken a dongle
23 1 has taken a dongle
24 1 is compiling
229 1 is debugging
431 1 is refactoring
1238 2 has taken a dongle
1240 2 has taken a dongle
1240 2 is compiling
1445 2 is debugging
1647 2 is refactoring
2472 1 has taken a dongle
2473 1 has taken a dongle
2474 1 is compiling
2678 1 is debugging
2879 1 is refactoring
3682 2 has taken a dongle
3684 2 has taken a dongle
3685 2 is compiling
3889 2 is debugging
4091 2 is refactoring
4916 1 has taken a dongle
4917 1 has taken a dongle
4918 1 is compiling
6129 2 has taken a dongle
6130 2 has taken a dongle
6130 2 is compiling

## Testing with 2 Coders, Burnout! FIFO

valgrind --tool=helgrind ./Codexion 2 100 200 200 200 3 100 fifo 2> dbm/debugging_2bf.txt


26 1 has taken a dongle
29 1 has taken a dongle
32 1 is compiling
109 2 burned out

## Testing with 2 Coders, Burnout! EDF

valgrind --tool=helgrind ./Codexion 2 100 200 200 200 3 100 edf 2> dbm/debugging_2be.txt


21 1 has taken a dongle
24 1 has taken a dongle
26 1 is compiling
107 2 burned out

# Testing 3

## Testing with 3 Coders, no Burnout FIFO

valgrind --tool=helgrind ./Codexion 3 8000 200 200 200 3 100 fifo 2> dbm/debugging_3sf.txt


33 3 has taken a dongle
36 3 has taken a dongle
37 3 is compiling
245 3 is debugging
364 1 has taken a dongle
365 1 has taken a dongle
366 1 is compiling
447 3 is refactoring
571 1 is debugging
696 2 has taken a dongle
698 2 has taken a dongle
699 2 is compiling
772 1 is refactoring
905 2 is debugging
1009 3 has taken a dongle
1010 3 has taken a dongle
1012 3 is compiling
1106 2 is refactoring
1217 3 is debugging
1322 1 has taken a dongle
1323 1 has taken a dongle
1325 1 is compiling
1419 3 is refactoring
1527 1 is debugging
1633 2 has taken a dongle
1635 2 has taken a dongle
1636 2 is compiling
1729 1 is refactoring
1840 2 is debugging
1940 3 has taken a dongle
1943 3 has taken a dongle
1944 3 is compiling
2041 2 is refactoring
2288 1 has taken a dongle
2289 1 has taken a dongle
2291 1 is compiling
2597 2 has taken a dongle
2598 2 has taken a dongle
2599 2 is compiling

## Testing with 3 Coders, no Burnout EDF

valgrind --tool=helgrind ./Codexion 3 10000 200 200 200 3 100 edf 2> dbm/debugging_3se.txt


28 1 has taken a dongle
32 1 has taken a dongle
34 1 is compiling
239 1 is debugging
341 3 has taken a dongle
343 3 has taken a dongle
344 3 is compiling
443 1 is refactoring
549 3 is debugging
683 2 has taken a dongle
684 2 has taken a dongle
685 2 is compiling
750 3 is refactoring
889 2 is debugging
1012 1 has taken a dongle
1013 1 has taken a dongle
1015 1 is compiling
1090 2 is refactoring
1219 1 is debugging
1320 3 has taken a dongle
1322 3 has taken a dongle
1323 3 is compiling
1422 1 is refactoring
1529 3 is debugging
1629 2 has taken a dongle
1631 2 has taken a dongle
1633 2 is compiling
1730 3 is refactoring
1836 2 is debugging
1942 1 has taken a dongle
1944 1 has taken a dongle
1945 1 is compiling
2037 2 is refactoring
2248 3 has taken a dongle
2249 3 has taken a dongle
2250 3 is compiling
2558 2 has taken a dongle
2558 2 has taken a dongle
2559 2 is compiling

## Testing with 3 Coders, no Burnout FIFO, long cooldown

valgrind --tool=helgrind ./Codexion 3 12000 200 200 200 3 1000 fifo 2> dbm/debugging_3lf.txt


33 1 has taken a dongle
38 1 has taken a dongle
40 1 is compiling
245 1 is debugging
447 1 is refactoring
1250 3 has taken a dongle
1251 3 has taken a dongle
1254 3 is compiling
1456 3 is debugging
1658 3 is refactoring
2468 2 has taken a dongle
2470 2 has taken a dongle
2472 2 is compiling
2675 2 is debugging
2877 2 is refactoring
3681 1 has taken a dongle
3683 1 has taken a dongle
3685 1 is compiling
3889 1 is debugging
4091 1 is refactoring
4893 3 has taken a dongle
4896 3 has taken a dongle
4898 3 is compiling
5101 3 is debugging
5302 3 is refactoring
6121 2 has taken a dongle
6122 2 has taken a dongle
6123 2 is compiling
6327 2 is debugging
6530 2 is refactoring
7333 1 has taken a dongle
7336 1 has taken a dongle
7337 1 is compiling
8558 3 has taken a dongle
8558 3 has taken a dongle
8559 3 is compiling
9765 2 has taken a dongle
9767 2 has taken a dongle
9768 2 is compiling

## Testing with 3 Coders, no Burnout EDF, long cooldown

valgrind --tool=helgrind ./Codexion 3 14000 200 200 200 3 1000 edf 2> dbm/debugging_3le.txt


28 3 has taken a dongle
32 3 has taken a dongle
34 3 is compiling
240 3 is debugging
441 3 is refactoring
1245 1 has taken a dongle
1249 1 has taken a dongle
1251 1 is compiling
1454 1 is debugging
1655 1 is refactoring
2482 2 has taken a dongle
2483 2 has taken a dongle
2485 2 is compiling
2688 2 is debugging
2889 2 is refactoring
3691 3 has taken a dongle
3693 3 has taken a dongle
3694 3 is compiling
3898 3 is debugging
4098 3 is refactoring
4924 1 has taken a dongle
4924 1 has taken a dongle
4925 1 is compiling
5127 1 is debugging
5329 1 is refactoring
6134 2 has taken a dongle
6136 2 has taken a dongle
6137 2 is compiling
6342 2 is debugging
6543 2 is refactoring
7345 3 has taken a dongle
7348 3 has taken a dongle
7350 3 is compiling
8575 1 has taken a dongle
8576 1 has taken a dongle
8577 1 is compiling
9781 2 has taken a dongle
9782 2 has taken a dongle
9783 2 is compiling

## Testing with 3 Coders, Burnout! FIFO

valgrind --tool=helgrind ./Codexion 3 100 200 200 200 3 100 fifo 2> dbm/debugging_3bf.txt


65 3 has taken a dongle
68 3 has taken a dongle
70 3 is compiling
108 1 burned out

## Testing with 3 Coders, Burnout! EDF

valgrind --tool=helgrind ./Codexion 3 100 200 200 200 3 100 edf 2> dbm/debugging_3be.txt


39 1 has taken a dongle
41 1 has taken a dongle
43 1 is compiling
108 2 burned out

# Testing 50

## Testing with 50 Coders, no Burnout FIFO

valgrind --tool=helgrind ./Codexion 50 12000 200 200 200 3 100 fifo 2> dbm/debugging_50sf.txt


243 29 has taken a dongle
250 29 has taken a dongle
261 29 is compiling
286 27 has taken a dongle
486 13 has taken a dongle
721 13 has taken a dongle
723 45 has taken a dongle
807 45 has taken a dongle
810 45 is compiling
810 19 has taken a dongle
816 17 has taken a dongle
839 17 has taken a dongle
840 39 has taken a dongle
842 3 has taken a dongle
873 27 has taken a dongle
875 23 has taken a dongle
876 15 has taken a dongle
878 7 has taken a dongle
882 41 has taken a dongle
888 47 has taken a dongle
895 5 has taken a dongle
896 21 has taken a dongle
898 37 has taken a dongle
911 1 has taken a dongle
913 29 is debugging
915 35 has taken a dongle
930 13 is compiling
931 33 has taken a dongle
933 25 has taken a dongle
935 31 has taken a dongle
936 19 has taken a dongle
938 43 has taken a dongle
943 39 has taken a dongle
945 17 is compiling
946 9 has taken a dongle
966 27 is compiling
969 15 has taken a dongle
972 3 has taken a dongle
974 7 has taken a dongle
975 41 has taken a dongle
977 23 has taken a dongle
984 47 has taken a dongle
986 21 has taken a dongle
987 5 has taken a dongle
988 37 has taken a dongle
990 1 has taken a dongle
991 19 is compiling
993 35 has taken a dongle
1045 25 has taken a dongle
1047 31 has taken a dongle
1057 43 has taken a dongle
1064 33 has taken a dongle
1068 15 is compiling
1070 7 is compiling
1116 39 is compiling
1121 41 is compiling
1123 3 is compiling
1145 47 is compiling
1147 9 has taken a dongle
1153 37 is compiling
1155 23 is compiling
1158 45 is debugging
1160 21 is compiling
1161 1 is compiling
1162 5 is compiling
1163 31 is compiling
1165 43 is compiling
1166 35 is compiling
1169 25 is compiling
1181 33 is compiling
1182 29 is refactoring
1184 13 is debugging
1187 9 is compiling
1189 17 is debugging
1197 27 is debugging
1257 19 is debugging
1362 45 is refactoring
1377 43 is debugging
1391 13 is refactoring
1440 17 is refactoring
1442 47 is debugging
1610 27 is refactoring
1612 3 is debugging
1615 19 is refactoring
1617 33 is debugging
1631 20 has taken a dongle
1709 44 has taken a dongle
1755 21 is debugging
1757 50 has taken a dongle
1759 35 is debugging
2018 31 is debugging
2031 28 has taken a dongle
2033 1 is debugging
2038 43 is refactoring
2039 15 is debugging
2041 18 has taken a dongle
2041 5 is debugging
2049 37 is debugging
2050 7 is debugging
2056 41 is debugging
2057 25 is debugging
2058 9 is debugging
2068 46 has taken a dongle
2071 16 has taken a dongle
2076 2 has taken a dongle
2077 30 has taken a dongle
2078 24 has taken a dongle
2080 23 is debugging
2084 39 is debugging
2106 20 has taken a dongle
2108 14 has taken a dongle
2112 26 has taken a dongle
2113 6 has taken a dongle
2115 44 has taken a dongle
2135 47 is refactoring
2158 3 is refactoring
2159 33 is refactoring
2164 34 has taken a dongle
2166 42 has taken a dongle
2169 21 is refactoring
2171 40 has taken a dongle
2172 4 has taken a dongle
2173 22 has taken a dongle
2174 38 has taken a dongle
2176 10 has taken a dongle
2177 32 has taken a dongle
2178 50 has taken a dongle
2180 28 has taken a dongle
2181 8 has taken a dongle
2182 36 has taken a dongle
2184 18 has taken a dongle
2185 46 has taken a dongle
2187 30 has taken a dongle
2224 16 has taken a dongle
2226 14 has taken a dongle
2228 26 has taken a dongle
2229 2 has taken a dongle
2230 24 has taken a dongle
2231 6 has taken a dongle
2233 31 is refactoring
2235 44 is compiling
2237 40 has taken a dongle
2238 42 has taken a dongle
2240 4 has taken a dongle
2241 10 has taken a dongle
2242 36 has taken a dongle
2244 22 has taken a dongle
2245 35 is refactoring
2247 20 is compiling
2248 6 is compiling
2250 5 is refactoring
2289 34 has taken a dongle
2290 1 is refactoring
2292 50 is compiling
2293 15 is refactoring
2321 28 is compiling
2322 14 is compiling
2324 18 is compiling
2326 37 is refactoring
2328 42 is compiling
2330 7 is refactoring
2332 22 is compiling
2334 41 is refactoring
2369 25 is refactoring
2370 40 is compiling
2373 26 is compiling
2374 24 is compiling
2386 38 has taken a dongle
2387 30 is compiling
2389 9 is refactoring
2391 46 is compiling
2393 36 is compiling
2394 16 is compiling
2395 32 has taken a dongle
2396 23 is refactoring
2404 2 is compiling
2405 4 is compiling
2407 10 is compiling
2407 8 has taken a dongle
2409 39 is refactoring
2410 34 is compiling
2411 38 is compiling
2412 32 is compiling
2469 8 is compiling
2531 20 is debugging
2564 44 is debugging
2593 50 is debugging
2608 6 is debugging
2609 28 is debugging
2628 22 is debugging
2713 14 is debugging
2715 18 is debugging
2718 42 is debugging
2745 30 is debugging
2762 46 is debugging
2765 20 is refactoring
2790 2 is debugging
2816 49 has taken a dongle
2864 40 is debugging
3004 26 is debugging
3031 36 is debugging
3187 10 is debugging
3192 16 is debugging
3206 24 is debugging
3238 32 is debugging
3239 19 has taken a dongle
3290 29 has taken a dongle
3639 4 is debugging
3640 38 is debugging
3642 34 is debugging
3643 44 is refactoring
3648 50 is refactoring
3650 6 is refactoring
3657 41 has taken a dongle
3672 43 has taken a dongle
3674 23 has taken a dongle
3675 28 is refactoring
3679 31 has taken a dongle
3681 15 has taken a dongle
3926 15 has taken a dongle
3927 11 has taken a dongle
3945 9 has taken a dongle
3949 49 has taken a dongle
3970 8 is debugging
3980 22 is refactoring
3982 14 is refactoring
3984 18 is refactoring
3986 42 is refactoring
4031 5 has taken a dongle
4033 30 is refactoring
4036 46 is refactoring
4045 21 has taken a dongle
4136 21 has taken a dongle
4137 21 is compiling
4269 33 has taken a dongle
4270 35 has taken a dongle
4272 1 has taken a dongle
4273 37 has taken a dongle
4274 17 has taken a dongle
4276 3 has taken a dongle
4277 27 has taken a dongle
4278 2 is refactoring
4280 45 has taken a dongle
4281 39 has taken a dongle
4282 40 is refactoring
4283 26 is refactoring
4284 19 has taken a dongle
4286 36 is refactoring
4287 10 is refactoring
4313 7 has taken a dongle
4314 16 is refactoring
4316 24 is refactoring
4316 1 has taken a dongle
4318 29 has taken a dongle
4319 23 has taken a dongle
4365 43 has taken a dongle
4366 41 has taken a dongle
4369 4 is refactoring
4370 38 is refactoring
4373 34 is refactoring
4374 31 has taken a dongle
4376 15 is compiling
4377 9 has taken a dongle
4379 11 has taken a dongle
4380 5 has taken a dongle
4382 25 has taken a dongle
4407 8 is refactoring
4408 49 is compiling
4410 37 has taken a dongle
4412 27 has taken a dongle
4413 17 has taken a dongle
4415 45 has taken a dongle
4417 39 has taken a dongle
4419 33 has taken a dongle
4425 19 is compiling
4429 32 is refactoring
4431 35 has taken a dongle
4433 29 is compiling
4435 43 is compiling
4451 23 is compiling
4454 7 has taken a dongle
4456 41 is compiling
4458 5 is compiling
4459 31 is compiling
4460 3 has taken a dongle
4462 1 is compiling
4463 9 is compiling
4465 37 is compiling
4466 45 is compiling
4468 25 has taken a dongle
4470 11 is compiling
4472 27 is compiling
4473 33 is compiling
4475 39 is compiling
4477 35 is compiling
4478 17 is compiling
4504 7 is compiling
4506 3 is compiling
4507 25 is compiling
4514 21 is debugging
4709 49 is debugging
4732 5 is debugging
4840 21 is refactoring
4850 29 is debugging
4855 11 is debugging
4860 41 is debugging
4932 49 is refactoring
4992 27 is debugging
4992 9 is debugging
4999 31 is debugging
5320 33 is debugging
5322 37 is debugging
5339 43 is debugging
5373 19 is debugging
5394 15 is debugging
5548 23 is debugging
5553 5 is refactoring
5587 29 is refactoring
5598 11 is refactoring
5678 25 is debugging
5688 35 is debugging
5727 1 is debugging
5739 50 has taken a dongle
5756 50 has taken a dongle
5757 50 is compiling
5763 42 has taken a dongle
5765 42 has taken a dongle
5766 42 is compiling
5772 30 has taken a dongle
5774 3 is debugging
5995 50 is debugging
6008 44 has taken a dongle
6010 41 is refactoring
6011 7 is debugging
6017 18 has taken a dongle
6019 45 is debugging
6109 27 is refactoring
6308 9 is refactoring
6309 6 has taken a dongle
6351 16 has taken a dongle
6353 28 has taken a dongle
6354 17 is debugging
6359 26 has taken a dongle
6396 4 has taken a dongle
6469 22 has taken a dongle
6473 10 has taken a dongle
6536 20 has taken a dongle
6691 24 has taken a dongle
6693 38 has taken a dongle
6744 40 has taken a dongle
6746 36 has taken a dongle
6757 38 has taken a dongle
6759 38 is compiling
6762 33 is refactoring
6854 32 has taken a dongle
6993 37 is refactoring
6999 12 has taken a dongle
7001 34 has taken a dongle
7017 43 is refactoring
7082 8 has taken a dongle
7099 8 has taken a dongle
7100 15 is refactoring
7131 23 is refactoring
7132 25 is refactoring
7137 35 is refactoring
7140 1 is refactoring
7142 30 has taken a dongle
7180 48 has taken a dongle
7181 39 is debugging
7183 42 is debugging
7184 18 has taken a dongle
7186 44 has taken a dongle
7187 3 is refactoring
7219 50 is refactoring
7221 7 is refactoring
7223 44 is compiling
7225 6 has taken a dongle
7227 28 has taken a dongle
7228 16 has taken a dongle
7230 26 has taken a dongle
7267 22 has taken a dongle
7270 10 has taken a dongle
7272 17 is refactoring
7334 4 has taken a dongle
7335 20 has taken a dongle
7336 24 has taken a dongle
7412 2 has taken a dongle
7413 31 is refactoring
7415 40 has taken a dongle
7417 36 has taken a dongle
7418 38 is debugging
7442 32 has taken a dongle
7443 34 has taken a dongle
7445 12 has taken a dongle
7446 19 is refactoring
7472 8 is compiling
7473 30 is compiling
7491 48 has taken a dongle
7493 45 is refactoring
7495 18 is compiling
7496 16 is compiling
7497 28 is compiling
7498 6 is compiling
7516 22 is compiling
7518 26 is compiling
7520 10 is compiling
7521 39 is refactoring
7640 42 is refactoring
7642 20 is compiling
7643 4 is compiling
7652 24 is compiling
7654 2 has taken a dongle
7656 32 is compiling
7657 36 is compiling
7659 40 is compiling
7660 44 is debugging
7661 34 is compiling
7662 12 is compiling
7665 48 is compiling
7683 43 has taken a dongle
7685 38 is refactoring
7723 8 is debugging
7792 43 has taken a dongle
7799 30 is debugging
7801 26 is debugging
7851 16 is debugging
7863 28 is debugging
7864 22 is debugging
7866 10 is debugging
7891 2 is compiling
7893 44 is refactoring
7899 18 is debugging
7910 12 is debugging
7982 24 is debugging
8129 20 is debugging
8130 43 is compiling
8131 8 is refactoring
8133 29 has taken a dongle
8136 30 is refactoring
8141 26 is refactoring
8142 16 is refactoring
8143 28 is refactoring
8154 22 is refactoring
8155 10 is refactoring
8156 34 is debugging
8158 4 is debugging
8163 27 has taken a dongle
8164 18 is refactoring
8165 17 has taken a dongle
8170 19 has taken a dongle
8171 6 is debugging
8173 48 is debugging
8228 12 is refactoring
8238 7 has taken a dongle
8286 32 is debugging
8288 11 has taken a dongle
8294 17 has taken a dongle
8414 36 is debugging
8417 29 has taken a dongle
8418 41 has taken a dongle
8424 9 has taken a dongle
8461 23 has taken a dongle
8463 24 is refactoring
8467 20 is refactoring
8472 21 has taken a dongle
8483 33 has taken a dongle
8497 40 is debugging
8499 34 is refactoring
8500 4 is refactoring
8523 19 has taken a dongle
8524 7 has taken a dongle
8544 6 is refactoring
8545 35 has taken a dongle
8546 27 has taken a dongle
8547 49 has taken a dongle
8548 31 has taken a dongle
8549 48 is refactoring
8552 11 has taken a dongle
8559 17 is compiling
8560 5 has taken a dongle
8562 41 has taken a dongle
8589 47 has taken a dongle
8590 2 is debugging
8607 39 has taken a dongle
8608 9 has taken a dongle
8609 21 has taken a dongle
8610 32 is refactoring
8611 13 has taken a dongle
8612 25 has taken a dongle
8613 23 has taken a dongle
8614 33 has taken a dongle
8615 3 has taken a dongle
8617 36 is refactoring
8646 29 is compiling
8647 7 is compiling
8649 35 has taken a dongle
8651 37 has taken a dongle
8684 11 is compiling
8686 27 is compiling
8688 31 has taken a dongle
8689 49 has taken a dongle
8690 47 has taken a dongle
8691 41 is compiling
8692 19 is compiling
8693 9 is compiling
8695 25 has taken a dongle
8696 39 has taken a dongle
8697 33 is compiling
8699 21 is compiling
8700 5 has taken a dongle
8708 13 has taken a dongle
8749 35 is compiling
8751 3 has taken a dongle
8753 23 is compiling
8754 40 is refactoring
8770 1 has taken a dongle
8771 31 is compiling
8774 47 is compiling
8782 49 is compiling
8784 5 is compiling
8785 39 is compiling
8787 37 has taken a dongle
8792 13 is compiling
8807 2 is refactoring
8810 37 is compiling
8871 25 is compiling
8892 3 is compiling
8901 1 has taken a dongle
8966 1 is compiling
9015 47 is debugging
9044 42 has taken a dongle
9046 13 is debugging
9105 11 is debugging
9112 42 has taken a dongle
9118 49 is debugging
9126 8 has taken a dongle
9144 42 is compiling
9171 34 has taken a dongle
9269 12 has taken a dongle
9297 46 has taken a dongle
9299 47 is refactoring
9305 48 has taken a dongle
9307 40 has taken a dongle
9308 20 has taken a dongle
9313 13 is refactoring
9530 11 is refactoring
9532 8 has taken a dongle
9553 49 is refactoring
9554 48 has taken a dongle
9560 6 has taken a dongle
9588 18 has taken a dongle
9590 32 has taken a dongle
9604 4 has taken a dongle
9619 46 has taken a dongle
9759 22 has taken a dongle
9760 36 has taken a dongle
9762 12 has taken a dongle
9764 28 has taken a dongle
9816 20 has taken a dongle
9818 24 has taken a dongle
9819 10 has taken a dongle
9820 30 has taken a dongle
9821 8 is compiling
9822 38 has taken a dongle
9824 18 has taken a dongle
9825 6 has taken a dongle
9826 40 has taken a dongle
9827 32 has taken a dongle
9828 48 is compiling
9830 14 has taken a dongle
9831 4 has taken a dongle
9832 34 has taken a dongle
9833 26 has taken a dongle
9834 50 has taken a dongle
9835 46 is compiling
9844 2 has taken a dongle
9845 36 has taken a dongle
9846 12 is compiling
9847 22 has taken a dongle
9858 20 is compiling
9860 28 has taken a dongle
9861 50 has taken a dongle
9862 14 has taken a dongle
9863 4 is compiling
9864 34 is compiling
9865 10 has taken a dongle
9866 32 is compiling
9868 18 is compiling
9886 40 is compiling
9889 26 has taken a dongle
9890 30 has taken a dongle
9891 36 is compiling
9892 24 has taken a dongle
9893 6 is compiling
9894 22 is compiling
9896 38 has taken a dongle
9897 14 is compiling
9899 28 is compiling
9900 50 is compiling
9905 2 has taken a dongle
9953 38 is compiling
9973 10 is compiling
9974 24 is compiling
9976 26 is compiling
9978 30 is compiling
9980 2 is compiling
10125 48 is debugging
10140 46 is debugging
10305 14 is debugging
10406 48 is refactoring
10408 46 is refactoring
10446 47 has taken a dongle
10447 12 is debugging
10453 45 has taken a dongle
10475 49 has taken a dongle
10476 47 has taken a dongle
10481 45 has taken a dongle
10490 13 has taken a dongle
10504 45 is compiling
10506 15 has taken a dongle
10508 47 is compiling
10510 49 has taken a dongle
10512 13 has taken a dongle
10514 15 has taken a dongle
10517 49 is compiling
10519 13 is compiling
10525 11 has taken a dongle
10526 15 is compiling
10528 11 has taken a dongle
10531 11 is compiling
10606 14 is refactoring
10653 12 is refactoring
10822 44 has taken a dongle
10823 44 has taken a dongle
10825 44 is compiling
10838 46 has taken a dongle
10846 46 has taken a dongle
10878 48 has taken a dongle
10879 14 has taken a dongle
10888 16 has taken a dongle
10891 14 has taken a dongle
10897 14 is compiling
10903 46 is compiling
10907 12 has taken a dongle
10908 16 has taken a dongle
10910 48 has taken a dongle
10911 12 has taken a dongle
10914 16 is compiling
10915 48 is compiling
10925 12 is compiling

## Testing with 50 Coders, no Burnout EDF

valgrind --tool=helgrind ./Codexion 50 12000 200 200 200 3 100 edf 2> dbm/debugging_50se.txt


150 15 has taken a dongle
157 15 has taken a dongle
427 37 has taken a dongle
428 27 has taken a dongle
452 1 has taken a dongle
518 9 has taken a dongle
519 31 has taken a dongle
522 23 has taken a dongle
523 43 has taken a dongle
606 25 has taken a dongle
607 47 has taken a dongle
608 13 has taken a dongle
641 41 has taken a dongle
643 29 has taken a dongle
643 45 has taken a dongle
657 15 is compiling
658 7 has taken a dongle
662 37 has taken a dongle
664 49 has taken a dongle
665 23 has taken a dongle
670 9 has taken a dongle
681 33 has taken a dongle
683 31 has taken a dongle
687 3 has taken a dongle
700 11 has taken a dongle
701 21 has taken a dongle
703 25 has taken a dongle
704 47 has taken a dongle
705 39 has taken a dongle
706 29 has taken a dongle
707 1 has taken a dongle
708 41 has taken a dongle
709 43 has taken a dongle
710 27 has taken a dongle
711 45 has taken a dongle
716 49 has taken a dongle
718 9 is compiling
719 31 is compiling
721 23 is compiling
722 27 is compiling
725 1 is compiling
736 45 is compiling
740 19 has taken a dongle
741 43 is compiling
742 37 is compiling
766 21 has taken a dongle
786 29 is compiling
787 25 is compiling
789 41 is compiling
791 13 has taken a dongle
868 3 has taken a dongle
874 7 has taken a dongle
878 33 has taken a dongle
880 49 is compiling
886 39 has taken a dongle
920 11 has taken a dongle
946 21 is compiling
948 19 has taken a dongle
949 47 is compiling
951 13 is compiling
984 33 is compiling
986 3 is compiling
987 15 is debugging
990 7 is compiling
1004 9 is debugging
1006 39 is compiling
1008 11 is compiling
1045 23 is debugging
1050 31 is debugging
1067 27 is debugging
1068 43 is debugging
1070 37 is debugging
1071 1 is debugging
1077 45 is debugging
1092 19 is compiling
1094 29 is debugging
1098 25 is debugging
1157 16 has taken a dongle
1160 41 is debugging
1203 49 is debugging
1332 47 is debugging
1333 15 is refactoring
1494 9 is refactoring
1514 26 has taken a dongle
1516 30 has taken a dongle
1522 33 is debugging
1562 23 is refactoring
1568 43 is refactoring
1569 2 has taken a dongle
1570 2 has taken a dongle
1673 31 is refactoring
1691 37 is refactoring
1693 13 is debugging
1717 1 is refactoring
1719 24 has taken a dongle
1808 45 is refactoring
1814 29 is refactoring
1960 42 has taken a dongle
1964 44 has taken a dongle
1981 11 is debugging
1983 39 is debugging
1984 7 is debugging
1986 28 has taken a dongle
1987 21 is debugging
2059 16 has taken a dongle
2061 25 is refactoring
2124 50 has taken a dongle
2125 41 is refactoring
2126 40 has taken a dongle
2128 3 is debugging
2129 19 is debugging
2131 10 has taken a dongle
2132 8 has taken a dongle
2134 46 has taken a dongle
2135 14 has taken a dongle
2136 26 has taken a dongle
2137 34 has taken a dongle
2139 49 is refactoring
2140 12 has taken a dongle
2141 47 is refactoring
2246 32 has taken a dongle
2247 22 has taken a dongle
2374 30 has taken a dongle
2375 27 is refactoring
2377 20 has taken a dongle
2378 2 is compiling
2424 38 has taken a dongle
2426 48 has taken a dongle
2428 4 has taken a dongle
2430 33 is refactoring
2431 24 has taken a dongle
2432 13 is refactoring
2472 42 has taken a dongle
2474 44 has taken a dongle
2484 28 has taken a dongle
2485 16 is compiling
2487 50 has taken a dongle
2546 14 has taken a dongle
2547 8 has taken a dongle
2548 40 has taken a dongle
2549 46 has taken a dongle
2551 12 has taken a dongle
2552 11 is refactoring
2554 39 is refactoring
2556 7 is refactoring
2557 10 has taken a dongle
2559 26 is compiling
2560 34 has taken a dongle
2562 21 is refactoring
2564 3 is refactoring
2565 19 is refactoring
2566 32 has taken a dongle
2584 30 is compiling
2585 22 has taken a dongle
2587 4 has taken a dongle
2589 24 is compiling
2591 20 has taken a dongle
2604 38 has taken a dongle
2606 44 is compiling
2608 48 has taken a dongle
2610 28 is compiling
2611 50 is compiling
2683 12 is compiling
2685 34 is compiling
2687 42 is compiling
2699 40 is compiling
2701 14 is compiling
2702 32 is compiling
2703 4 is compiling
2719 8 is compiling
2721 46 is compiling
2723 10 is compiling
2725 48 is compiling
2727 22 is compiling
2781 38 is compiling
2782 20 is compiling
2785 2 is debugging
2815 16 is debugging
2831 30 is debugging
2862 28 is debugging
2871 24 is debugging
2903 26 is debugging
2929 44 is debugging
2956 8 is debugging
2980 32 is debugging
2981 50 is debugging
2983 10 is debugging
2985 12 is debugging
2987 42 is debugging
2989 17 has taken a dongle
2996 34 is debugging
3004 14 is debugging
3048 2 is refactoring
3050 40 is debugging
3097 46 is debugging
3098 27 has taken a dongle
3226 48 is debugging
3228 16 is refactoring
3234 35 has taken a dongle
3271 22 is debugging
3276 30 is refactoring
3277 28 is refactoring
3279 38 is debugging
3285 4 is debugging
3427 25 has taken a dongle
3428 11 has taken a dongle
3430 9 has taken a dongle
3474 24 is refactoring
3491 41 has taken a dongle
3515 1 has taken a dongle
3556 26 is refactoring
3561 43 has taken a dongle
3562 17 has taken a dongle
3565 20 is debugging
3572 33 has taken a dongle
3575 44 is refactoring
3594 5 has taken a dongle
3597 47 has taken a dongle
3616 8 is refactoring
3618 32 is refactoring
3619 50 is refactoring
3621 10 is refactoring
3622 49 has taken a dongle
3623 12 is refactoring
3624 42 is refactoring
3626 34 is refactoring
3655 3 has taken a dongle
3656 45 has taken a dongle
3675 29 has taken a dongle
3676 15 has taken a dongle
3677 39 has taken a dongle
3679 14 is refactoring
3680 13 has taken a dongle
3693 23 has taken a dongle
3694 46 is refactoring
3727 29 has taken a dongle
3728 35 has taken a dongle
3730 27 has taken a dongle
3733 21 has taken a dongle
3757 48 is refactoring
3767 11 has taken a dongle
3768 25 has taken a dongle
3780 31 has taken a dongle
3781 9 has taken a dongle
3805 22 is refactoring
3806 38 is refactoring
3811 41 has taken a dongle
3812 1 has taken a dongle
3815 43 has taken a dongle
3817 17 is compiling
3819 33 has taken a dongle
3821 4 is refactoring
3838 49 has taken a dongle
3840 5 has taken a dongle
3842 47 has taken a dongle
3843 3 has taken a dongle
3847 45 has taken a dongle
3849 15 has taken a dongle
3879 39 has taken a dongle
3901 23 has taken a dongle
3902 13 has taken a dongle
3903 40 is refactoring
3918 29 is compiling
3919 27 is compiling
3921 35 is compiling
3922 21 has taken a dongle
3930 20 is refactoring
3932 31 has taken a dongle
3937 11 is compiling
3939 25 is compiling
3947 9 is compiling
3954 41 is compiling
3958 1 is compiling
3959 43 is compiling
4009 5 is compiling
4010 49 is compiling
4020 45 is compiling
4022 3 is compiling
4023 47 is compiling
4025 33 is compiling
4026 13 is compiling
4038 15 is compiling
4053 23 is compiling
4055 39 is compiling
4056 21 is compiling
4059 31 is compiling
4061 17 is debugging
4224 29 is debugging
4249 49 is debugging
4262 17 is refactoring
4308 21 is debugging
4470 11 is debugging
4475 35 is debugging
4477 13 is debugging
4528 45 is debugging
4615 33 is debugging
4621 31 is debugging
4623 36 has taken a dongle
5011 41 is debugging
5017 1 is debugging
5074 27 is debugging
5076 46 has taken a dongle
5082 29 is refactoring
5084 18 has taken a dongle
5086 49 is refactoring
5088 15 is debugging
5093 23 is debugging
5094 47 is debugging
5105 43 is debugging
5123 9 is debugging
5124 25 is debugging
5130 39 is debugging
5132 10 has taken a dongle
5133 32 has taken a dongle
5134 21 is refactoring
5264 11 is refactoring
5265 35 is refactoring
5271 13 is refactoring
5272 50 has taken a dongle
5274 30 has taken a dongle
5395 45 is refactoring
5400 33 is refactoring
5402 31 is refactoring
5409 42 has taken a dongle
5410 3 is debugging
5475 48 has taken a dongle
5481 24 has taken a dongle
5482 28 has taken a dongle
5483 44 has taken a dongle
5485 36 has taken a dongle
5489 2 has taken a dongle
5490 5 is debugging
5492 16 has taken a dongle
5497 14 has taken a dongle
5498 46 has taken a dongle
5500 4 has taken a dongle
5504 32 has taken a dongle
5505 12 has taken a dongle
5516 18 has taken a dongle
5517 34 has taken a dongle
5519 6 has taken a dongle
5524 22 has taken a dongle
5526 41 is refactoring
5532 1 is refactoring
5533 27 is refactoring
5535 15 is refactoring
5564 23 is refactoring
5565 47 is refactoring
5571 10 has taken a dongle
5573 50 has taken a dongle
5579 43 is refactoring
5581 9 is refactoring
5583 25 is refactoring
5590 39 is refactoring
5596 40 has taken a dongle
5598 30 has taken a dongle
5600 18 is compiling
5608 44 has taken a dongle
5611 2 has taken a dongle
5614 24 has taken a dongle
5616 6 has taken a dongle
5617 46 is compiling
5619 12 has taken a dongle
5621 26 has taken a dongle
5622 10 is compiling
5623 2 is compiling
5628 16 has taken a dongle
5672 50 is compiling
5675 44 is compiling
5677 24 is compiling
5679 22 has taken a dongle
5685 36 is compiling
5687 34 has taken a dongle
5688 48 has taken a dongle
5690 32 is compiling
5691 4 has taken a dongle
5692 12 is compiling
5738 28 has taken a dongle
5739 30 is compiling
5746 40 has taken a dongle
5747 42 has taken a dongle
5749 14 has taken a dongle
5758 6 is compiling
5763 26 has taken a dongle
5786 3 is refactoring
5801 16 is compiling
5803 5 is refactoring
5804 34 is compiling
5805 22 is compiling
5829 4 is compiling
5848 48 is compiling
5849 42 is compiling
5851 14 is compiling
5852 28 is compiling
5902 40 is compiling
5918 26 is compiling
5921 10 is debugging
5924 18 is debugging
5953 46 is debugging
5955 50 is debugging
5968 32 is debugging
5988 2 is debugging
6027 24 is debugging
6028 44 is debugging
6030 6 is debugging
6037 19 has taken a dongle
6115 34 is debugging
6122 12 is debugging
6128 22 is debugging
6188 36 is debugging
6361 30 is debugging
6371 48 is debugging
6372 10 is refactoring
6378 18 is refactoring
6423 46 is refactoring
6526 50 is refactoring
6527 45 has taken a dongle
6529 11 has taken a dongle
6534 16 is debugging
6570 32 is refactoring
6572 19 has taken a dongle
6577 14 is debugging
6578 4 is debugging
6689 2 is refactoring
6690 24 is refactoring
6692 44 is refactoring
6742 6 is refactoring
6743 26 is debugging
6744 28 is debugging
6745 33 has taken a dongle
6746 35 has taken a dongle
6748 37 has taken a dongle
6750 15 has taken a dongle
6751 13 has taken a dongle
6752 1 has taken a dongle
6754 31 has taken a dongle
6755 34 is refactoring
6763 43 has taken a dongle
6765 12 is refactoring
6767 47 has taken a dongle
6768 7 has taken a dongle
6769 49 has taken a dongle
6770 17 has taken a dongle
6771 42 is debugging
6772 23 has taken a dongle
6790 25 has taken a dongle
6791 22 is refactoring
6806 29 has taken a dongle
6807 3 has taken a dongle
6809 5 has taken a dongle
6810 40 is debugging
6812 41 has taken a dongle
6813 27 has taken a dongle
6814 36 is refactoring
6816 30 is refactoring
6817 48 is refactoring
6818 25 has taken a dongle
6841 19 is compiling
6870 45 has taken a dongle
6958 33 has taken a dongle
6959 13 has taken a dongle
6991 16 is refactoring
6993 35 has taken a dongle
6994 7 has taken a dongle
6995 15 has taken a dongle
6997 14 is refactoring
6998 49 has taken a dongle
7000 47 has taken a dongle
7000 1 has taken a dongle
7001 17 has taken a dongle
7002 23 has taken a dongle
7003 11 has taken a dongle
7004 37 has taken a dongle
7005 29 has taken a dongle
7015 27 has taken a dongle
7075 31 has taken a dongle
7076 43 has taken a dongle
7078 3 has taken a dongle
7079 5 has taken a dongle
7080 41 has taken a dongle
7081 4 is refactoring
7083 26 is refactoring
7084 28 is refactoring
7086 25 is compiling
7087 33 is compiling
7089 42 is refactoring
7091 45 is compiling
7092 35 is compiling
7094 7 is compiling
7095 15 is compiling
7097 40 is refactoring
7098 13 is compiling
7115 23 is compiling
7116 29 is compiling
7117 1 is compiling
7119 11 is compiling
7121 49 is compiling
7122 27 is compiling
7124 47 is compiling
7125 17 is compiling
7126 43 is compiling
7127 37 is compiling
7129 5 is compiling
7141 3 is compiling
7142 31 is compiling
7146 41 is compiling
7157 19 is debugging
7251 20 has taken a dongle
7268 20 has taken a dongle
7370 20 is compiling
7450 17 is debugging
7481 19 is refactoring
7511 7 is debugging
7513 5 is debugging
7731 37 is debugging
7737 35 is debugging
7739 44 has taken a dongle
7740 18 has taken a dongle
7741 32 has taken a dongle
7746 6 has taken a dongle
7749 36 has taken a dongle
7760 46 has taken a dongle
8048 17 is refactoring
8049 48 has taken a dongle
8051 7 is refactoring
8057 12 has taken a dongle
8059 38 has taken a dongle
8185 24 has taken a dongle
8506 24 has taken a dongle
8507 2 has taken a dongle
8509 24 is compiling
8512 16 has taken a dongle
8573 5 is refactoring
8869 37 is refactoring
8940 35 is refactoring
8941 34 has taken a dongle
9091 26 has taken a dongle
9094 36 has taken a dongle
9095 50 has taken a dongle
9163 8 has taken a dongle
9246 44 has taken a dongle
9248 18 has taken a dongle
9249 4 has taken a dongle
9306 20 is debugging
9307 6 has taken a dongle
9341 46 has taken a dongle
9343 14 has taken a dongle
9344 48 has taken a dongle
9349 42 has taken a dongle
9351 12 has taken a dongle
9352 32 has taken a dongle
9353 28 has taken a dongle
9354 38 has taken a dongle
9356 30 has taken a dongle
9357 21 has taken a dongle
9358 2 has taken a dongle
9359 16 has taken a dongle
9360 34 has taken a dongle
9362 36 is compiling
9369 26 has taken a dongle
9372 50 has taken a dongle
9373 8 has taken a dongle
9376 44 is compiling
9378 18 is compiling
9380 4 has taken a dongle
9382 6 is compiling
9388 14 has taken a dongle
9389 46 is compiling
9391 42 has taken a dongle
9393 48 is compiling
9396 16 is compiling
9422 32 is compiling
9423 2 is compiling
9424 21 has taken a dongle
9433 26 is compiling
9462 4 is compiling
9465 50 is compiling
9466 34 is compiling
9468 30 has taken a dongle
9469 28 has taken a dongle
9471 12 is compiling
9489 8 is compiling
9491 38 is compiling
9493 14 is compiling
9494 42 is compiling
9497 21 is compiling
9498 30 is compiling
9511 28 is compiling
9512 20 is refactoring
9716 6 is debugging
9781 38 is debugging
9917 6 is refactoring
10028 18 is debugging
10030 38 is refactoring
10035 36 is debugging
10058 5 has taken a dongle
10070 19 has taken a dongle
10075 35 has taken a dongle
10078 39 has taken a dongle
10080 39 has taken a dongle
10120 22 has taken a dongle
10122 8 is debugging
10127 5 has taken a dongle
10129 35 has taken a dongle
10130 19 has taken a dongle
10141 5 is compiling
10142 35 is compiling
10160 39 is compiling
10177 22 has taken a dongle
10180 17 has taken a dongle
10181 19 is compiling
10188 22 is compiling
10193 17 has taken a dongle
10197 37 has taken a dongle
10201 9 has taken a dongle
10203 17 is compiling
10208 9 has taken a dongle
10210 7 has taken a dongle
10212 37 has taken a dongle
10215 9 is compiling
10216 7 has taken a dongle
10225 37 is compiling
10226 7 is compiling
10230 18 is refactoring
10259 36 is refactoring
10329 8 is refactoring
10513 40 has taken a dongle
10516 40 has taken a dongle
10522 40 is compiling
10535 18 has taken a dongle
10565 20 has taken a dongle
10574 38 has taken a dongle
10592 38 has taken a dongle
10593 20 has taken a dongle
10600 20 is compiling
10601 6 has taken a dongle
10602 10 has taken a dongle
10606 18 has taken a dongle
10608 36 has taken a dongle
10610 36 has taken a dongle
10620 8 has taken a dongle
10622 8 has taken a dongle
10623 36 is compiling
10624 8 is compiling
10625 38 is compiling
10626 6 has taken a dongle
10628 6 is compiling
10629 18 is compiling
10630 10 has taken a dongle
10631 10 is compiling

## Testing with 50 Coders, no Burnout FIFO, long cooldown

valgrind --tool=helgrind ./Codexion 50 12000 200 200 200 3 1000 fifo 2> dbm/debugging_50lf.txt


124 1 has taken a dongle
130 1 has taken a dongle
222 47 has taken a dongle
237 25 has taken a dongle
293 45 has taken a dongle
553 25 has taken a dongle
555 21 has taken a dongle
725 39 has taken a dongle
727 1 is compiling
729 30 has taken a dongle
733 47 has taken a dongle
734 49 has taken a dongle
736 45 has taken a dongle
737 25 is compiling
739 43 has taken a dongle
742 35 has taken a dongle
743 11 has taken a dongle
745 7 has taken a dongle
752 23 has taken a dongle
815 39 has taken a dongle
816 35 has taken a dongle
818 11 has taken a dongle
824 7 has taken a dongle
845 45 is compiling
846 23 has taken a dongle
848 30 has taken a dongle
873 35 is compiling
874 17 has taken a dongle
877 21 has taken a dongle
878 37 has taken a dongle
879 27 has taken a dongle
881 47 is compiling
882 11 is compiling
957 19 has taken a dongle
960 23 is compiling
990 39 is compiling
1015 49 has taken a dongle
1017 43 has taken a dongle
1018 32 has taken a dongle
1023 21 is compiling
1024 27 has taken a dongle
1026 37 has taken a dongle
1028 49 is compiling
1109 15 has taken a dongle
1110 17 has taken a dongle
1112 19 has taken a dongle
1114 30 is compiling
1140 25 is debugging
1143 43 is compiling
1144 9 has taken a dongle
1145 32 has taken a dongle
1147 1 is debugging
1148 37 is compiling
1160 45 is debugging
1167 7 is compiling
1173 47 is debugging
1175 17 is compiling
1177 35 is debugging
1179 15 has taken a dongle
1180 19 is compiling
1181 27 is compiling
1183 9 has taken a dongle
1184 32 is compiling
1195 9 is compiling
1269 15 is compiling
1275 11 is debugging
1311 21 is debugging
1322 23 is debugging
1357 39 is debugging
1371 25 is refactoring
1372 1 is refactoring
1374 45 is refactoring
1377 47 is refactoring
1382 35 is refactoring
1394 37 is debugging
1395 49 is debugging
1397 30 is debugging
1432 19 is debugging
1458 7 is debugging
1465 43 is debugging
1497 32 is debugging
1530 17 is debugging
1531 11 is refactoring
1533 21 is refactoring
1561 15 is debugging
1564 9 is debugging
1566 23 is refactoring
1573 39 is refactoring
1637 27 is debugging
1642 37 is refactoring
1643 49 is refactoring
1645 30 is refactoring
1661 7 is refactoring
1663 19 is refactoring
1698 43 is refactoring
1732 32 is refactoring
1734 17 is refactoring
1779 15 is refactoring
1784 9 is refactoring
1843 27 is refactoring
2322 22 has taken a dongle
2367 22 has taken a dongle
2517 22 is compiling
2536 18 has taken a dongle
2541 18 has taken a dongle
2542 18 is compiling
2625 24 has taken a dongle
2830 44 has taken a dongle
2832 50 has taken a dongle
2833 50 has taken a dongle
2838 14 has taken a dongle
2840 46 has taken a dongle
2841 48 has taken a dongle
2846 20 has taken a dongle
2847 38 has taken a dongle
2848 40 has taken a dongle
2849 8 has taken a dongle
2854 10 has taken a dongle
2855 16 has taken a dongle
2856 50 is compiling
2869 14 has taken a dongle
2994 38 has taken a dongle
3005 44 has taken a dongle
3007 16 has taken a dongle
3008 20 has taken a dongle
3009 31 has taken a dongle
3013 40 has taken a dongle
3015 22 is debugging
3016 28 has taken a dongle
3020 26 has taken a dongle
3022 18 is debugging
3023 36 has taken a dongle
3024 8 has taken a dongle
3026 46 has taken a dongle
3027 38 is compiling
3029 8 is compiling
3033 28 has taken a dongle
3063 26 has taken a dongle
3074 16 is compiling
3077 36 has taken a dongle
3078 14 is compiling
3079 40 is compiling
3082 48 has taken a dongle
3083 24 has taken a dongle
3088 28 is compiling
3090 31 has taken a dongle
3098 10 has taken a dongle
3099 20 is compiling
3101 44 is compiling
3104 26 is compiling
3106 36 is compiling
3110 6 has taken a dongle
3112 24 is compiling
3177 31 is compiling
3258 22 is refactoring
3271 18 is refactoring
3273 33 has taken a dongle
3274 46 is compiling
3276 6 has taken a dongle
3278 8 is debugging
3292 10 is compiling
3318 48 is compiling
3364 50 is debugging
3393 33 has taken a dongle
3408 38 is debugging
3467 6 is compiling
3468 14 is debugging
3477 26 is debugging
3479 24 is debugging
3517 28 is debugging
3518 36 is debugging
3527 20 is debugging
3528 33 is compiling
3564 16 is debugging
3567 44 is debugging
3606 40 is debugging
3607 8 is refactoring
3611 31 is debugging
3612 46 is debugging
3613 48 is debugging
3614 50 is refactoring
3619 10 is debugging
3668 38 is refactoring
3678 14 is refactoring
3680 26 is refactoring
3721 28 is refactoring
3723 24 is refactoring
3729 36 is refactoring
3834 20 is refactoring
3919 6 is debugging
3921 33 is debugging
4056 16 is refactoring
4061 44 is refactoring
4122 6 is refactoring
4209 31 is refactoring
4308 48 is refactoring
4761 46 is refactoring
4766 10 is refactoring
4769 40 is refactoring
4781 33 is refactoring
4782 27 has taken a dongle
4963 23 has taken a dongle
4964 45 has taken a dongle
4970 17 has taken a dongle
5076 34 has taken a dongle
5293 25 has taken a dongle
5620 41 has taken a dongle
5672 23 has taken a dongle
5674 45 has taken a dongle
5679 21 has taken a dongle
5680 5 has taken a dongle
5681 27 has taken a dongle
5682 17 has taken a dongle
5688 34 has taken a dongle
5690 7 has taken a dongle
5691 15 has taken a dongle
5694 19 has taken a dongle
5713 32 has taken a dongle
5714 39 has taken a dongle
5715 27 is compiling
5717 25 has taken a dongle
5720 7 has taken a dongle
5721 21 has taken a dongle
5726 13 has taken a dongle
5877 21 is compiling
5944 37 has taken a dongle
5946 15 has taken a dongle
5947 17 is compiling
5949 41 has taken a dongle
5951 5 has taken a dongle
5952 49 has taken a dongle
5956 39 has taken a dongle
5987 47 has taken a dongle
5989 32 has taken a dongle
5991 19 has taken a dongle
6003 13 has taken a dongle
6018 34 is compiling
6023 29 has taken a dongle
6025 23 is compiling
6026 5 is compiling
6048 9 has taken a dongle
6057 25 is compiling
6059 45 is compiling
6158 49 has taken a dongle
6159 15 is compiling
6169 37 has taken a dongle
6171 47 has taken a dongle
6173 27 is debugging
6174 41 is compiling
6175 19 is compiling
6177 13 is compiling
6178 32 is compiling
6179 39 is compiling
6181 29 has taken a dongle
6183 7 is compiling
6186 47 is compiling
6187 49 is compiling
6189 21 is debugging
6191 17 is debugging
6193 37 is compiling
6194 9 has taken a dongle
6229 29 is compiling
6235 9 is compiling
6262 23 is debugging
6358 34 is debugging
6383 27 is refactoring
6396 25 is debugging
6482 21 is refactoring
6483 17 is refactoring
6489 15 is debugging
6491 5 is debugging
6509 7 is debugging
6513 45 is debugging
6533 32 is debugging
6598 41 is debugging
6600 37 is debugging
6612 23 is refactoring
6657 34 is refactoring
6682 47 is debugging
6683 39 is debugging
6863 13 is debugging
6864 49 is debugging
6870 19 is debugging
6878 9 is debugging
6879 25 is refactoring
6880 15 is refactoring
6885 47 is refactoring
6887 29 is debugging
7066 7 is refactoring
7074 45 is refactoring
7655 32 is refactoring
7661 41 is refactoring
7772 37 is refactoring
7984 5 is refactoring
8002 39 is refactoring
8011 13 is refactoring
8012 49 is refactoring
8018 19 is refactoring
8080 9 is refactoring
8081 29 is refactoring
8083 22 has taken a dongle
8097 35 has taken a dongle
8100 18 has taken a dongle
8106 16 has taken a dongle
8201 33 has taken a dongle
8211 40 has taken a dongle
8286 48 has taken a dongle
8288 6 has taken a dongle
8380 24 has taken a dongle
8381 42 has taken a dongle
8472 46 has taken a dongle
8573 28 has taken a dongle
8574 12 has taken a dongle
8604 26 has taken a dongle
8607 4 has taken a dongle
8619 20 has taken a dongle
8625 30 has taken a dongle
8626 18 has taken a dongle
8627 14 has taken a dongle
8628 35 has taken a dongle
8634 8 has taken a dongle
8635 22 has taken a dongle
8645 38 has taken a dongle
8654 40 has taken a dongle
8656 16 has taken a dongle
8657 24 has taken a dongle
8658 6 has taken a dongle
8659 48 has taken a dongle
8660 33 has taken a dongle
8662 42 has taken a dongle
8663 28 has taken a dongle
8664 26 has taken a dongle
8665 4 has taken a dongle
8693 46 has taken a dongle
8695 35 is compiling
8698 20 has taken a dongle
8730 8 has taken a dongle
8731 14 has taken a dongle
8732 30 has taken a dongle
8734 24 is compiling
8735 26 is compiling
8737 48 is compiling
8748 40 is compiling
8750 33 is compiling
8752 18 is compiling
8764 22 is compiling
8766 4 is compiling
8773 46 is compiling
8775 16 is compiling
8791 28 is compiling
8792 38 has taken a dongle
8793 6 is compiling
8794 8 is compiling
8796 12 has taken a dongle
8798 20 is compiling
8799 42 is compiling
8800 14 is compiling
8801 30 is compiling
8809 38 is compiling
8827 12 is compiling
8990 35 is debugging
9012 4 is debugging
9036 18 is debugging
9067 40 is debugging
9070 38 is debugging
9080 46 is debugging
9254 42 is debugging
9260 26 is debugging
9261 35 is refactoring
9291 4 is refactoring
9292 8 is debugging
9297 24 is debugging
9477 14 is debugging
9481 33 is debugging
9483 28 is debugging
9484 18 is refactoring
9485 40 is refactoring
9500 22 is debugging
9501 38 is refactoring
9587 48 is debugging
9709 20 is debugging
9711 30 is debugging
9716 6 is debugging
9773 46 is refactoring
9784 42 is refactoring
9786 26 is refactoring
9868 12 is debugging
9889 8 is refactoring
9890 16 is debugging
9909 24 is refactoring
9910 14 is refactoring
10056 28 is refactoring
10057 33 is refactoring
10141 22 is refactoring
10177 48 is refactoring
10178 20 is refactoring
10607 30 is refactoring
10620 6 is refactoring
10692 12 is refactoring
10696 16 is refactoring
10697 36 has taken a dongle
10735 23 has taken a dongle
10743 27 has taken a dongle
10954 34 has taken a dongle
10960 47 has taken a dongle
10962 39 has taken a dongle
10963 7 has taken a dongle
10964 29 has taken a dongle
10991 41 has taken a dongle
10992 11 has taken a dongle
10993 5 has taken a dongle
10997 17 has taken a dongle
11116 19 has taken a dongle
11118 21 has taken a dongle
11131 31 has taken a dongle
11132 3 has taken a dongle
11134 36 has taken a dongle
11139 23 has taken a dongle
11140 13 has taken a dongle
11142 34 has taken a dongle
11176 7 has taken a dongle
11177 27 has taken a dongle
11178 15 has taken a dongle
11180 39 has taken a dongle
11181 47 has taken a dongle
11182 5 has taken a dongle
11183 11 has taken a dongle
11185 31 has taken a dongle
11206 3 has taken a dongle
11208 29 has taken a dongle
11209 41 has taken a dongle
11210 13 has taken a dongle
11211 19 has taken a dongle
11212 21 has taken a dongle
11213 23 is compiling
11214 36 is compiling
11216 17 has taken a dongle
11217 7 is compiling
11219 15 has taken a dongle
11220 47 is compiling
11223 34 is compiling
11224 27 is compiling
11225 31 is compiling
11227 41 is compiling
11229 11 is compiling
11243 13 is compiling
11267 39 is compiling
11275 3 is compiling
11276 29 is compiling
11277 15 is compiling
11278 17 is compiling
11280 5 is compiling
11282 43 has taken a dongle
11283 21 is compiling
11291 25 has taken a dongle
11363 19 is compiling
11366 43 has taken a dongle
11490 25 has taken a dongle
11713 25 is compiling
11751 13 is debugging
11779 5 is debugging
11781 29 is debugging
11782 43 is compiling
11784 11 is debugging
11914 36 is debugging
11916 41 is debugging
11917 3 is debugging
11955 31 is debugging
11956 34 is debugging
11980 13 is refactoring
11992 5 is refactoring
11993 29 is refactoring
12012 43 is debugging
12061 2 burned out

## Testing with 50 Coders, no Burnout EDF, long cooldown

valgrind --tool=helgrind ./Codexion 50 12000 200 200 200 3 1000 edf 2> dbm/debugging_50le.txt


187 15 has taken a dongle
338 31 has taken a dongle
340 31 has taken a dongle
525 5 has taken a dongle
528 27 has taken a dongle
588 15 has taken a dongle
814 27 has taken a dongle
822 47 has taken a dongle
952 10 has taken a dongle
955 31 is compiling
959 13 has taken a dongle
1094 24 has taken a dongle
1100 5 has taken a dongle
1102 15 is compiling
1103 39 has taken a dongle
1105 29 has taken a dongle
1106 7 has taken a dongle
1125 47 has taken a dongle
1126 27 is compiling
1127 10 has taken a dongle
1131 37 has taken a dongle
1139 29 has taken a dongle
1622 21 has taken a dongle
1623 13 has taken a dongle
1625 1 has taken a dongle
1646 47 is compiling
1669 24 has taken a dongle
1675 17 has taken a dongle
1676 7 has taken a dongle
1677 10 is compiling
1678 31 is debugging
1680 19 has taken a dongle
1681 37 has taken a dongle
1682 5 is compiling
1683 15 is debugging
1686 39 has taken a dongle
1687 7 is compiling
1717 21 has taken a dongle
1718 1 has taken a dongle
1724 27 is debugging
1726 13 is compiling
1746 43 has taken a dongle
1748 24 is compiling
1755 37 is compiling
1756 21 is compiling
1758 17 has taken a dongle
1761 1 is compiling
1763 43 has taken a dongle
1788 43 is compiling
1840 19 has taken a dongle
1892 31 is refactoring
1894 15 is refactoring
1897 29 is compiling
1921 17 is compiling
1946 27 is refactoring
1952 19 is compiling
2010 13 is debugging
2092 39 is compiling
2274 5 is debugging
2278 10 is debugging
2279 7 is debugging
2315 43 is debugging
2316 1 is debugging
2579 47 is debugging
2703 21 is debugging
2713 29 is debugging
2795 19 is debugging
2796 37 is debugging
2802 13 is refactoring
2804 5 is refactoring
2805 10 is refactoring
2810 7 is refactoring
2812 43 is refactoring
2814 24 is debugging
3235 17 is debugging
3237 32 has taken a dongle
4089 1 is refactoring
4195 39 is debugging
4211 47 is refactoring
4223 21 is refactoring
4684 29 is refactoring
4685 19 is refactoring
4686 37 is refactoring
4688 12 has taken a dongle
4692 24 is refactoring
4693 17 is refactoring
4694 6 has taken a dongle
4699 18 has taken a dongle
4700 20 has taken a dongle
4701 14 has taken a dongle
4702 2 has taken a dongle
4940 28 has taken a dongle
5454 36 has taken a dongle
6057 50 has taken a dongle
6429 8 has taken a dongle
7026 8 has taken a dongle
7565 8 is compiling
7568 23 has taken a dongle
7569 23 has taken a dongle
7570 38 has taken a dongle
7650 39 is refactoring
7652 16 has taken a dongle
7653 14 has taken a dongle
7754 18 has taken a dongle
7755 20 has taken a dongle
7790 44 has taken a dongle
7792 12 has taken a dongle
7794 42 has taken a dongle
7795 2 has taken a dongle
7796 6 has taken a dongle
7798 28 has taken a dongle
7799 36 has taken a dongle
7801 50 has taken a dongle
7804 32 has taken a dongle
7805 26 has taken a dongle
7806 23 is compiling
7807 38 has taken a dongle
7811 16 has taken a dongle
7893 20 is compiling
7894 14 is compiling
7895 36 is compiling
7896 8 is debugging
7923 6 is compiling
7924 44 has taken a dongle
7952 42 has taken a dongle
7953 28 is compiling
7955 32 is compiling
7956 18 is compiling
7958 12 is compiling
7959 30 has taken a dongle
7961 26 has taken a dongle
8009 2 is compiling
8010 50 is compiling
8014 38 is compiling
8056 16 is compiling
8058 42 is compiling
8062 30 has taken a dongle
8066 26 is compiling
8142 44 is compiling
8199 8 is refactoring
8200 30 is compiling
8204 23 is debugging
8262 6 is debugging
8297 12 is debugging
8336 28 is debugging
8424 14 is debugging
8426 26 is debugging
8427 2 is debugging
8433 23 is refactoring
8464 6 is refactoring
8469 30 is debugging
8680 50 is debugging
8796 42 is debugging
8798 44 is debugging
8959 32 is debugging
9090 12 is refactoring
9320 16 is debugging
9419 36 is debugging
9422 18 is debugging
9427 28 is refactoring
9484 14 is refactoring
9535 26 is refactoring
9571 2 is refactoring
9576 20 is debugging
9579 30 is refactoring
9915 50 is refactoring
9920 42 is refactoring
9932 44 is refactoring
10190 38 is debugging
10247 32 is refactoring
10249 13 has taken a dongle
10285 31 has taken a dongle
10286 25 has taken a dongle
10291 22 has taken a dongle
10293 16 is refactoring
10294 36 is refactoring
10340 18 is refactoring
10485 20 is refactoring
10549 17 has taken a dongle
10560 41 has taken a dongle
10684 41 has taken a dongle
10685 19 has taken a dongle
10696 29 has taken a dongle
10793 7 has taken a dongle
10942 35 has taken a dongle
10943 1 has taken a dongle
10951 45 has taken a dongle
10957 15 has taken a dongle
10959 33 has taken a dongle
10962 9 has taken a dongle
10970 43 has taken a dongle
10987 49 has taken a dongle
11013 11 has taken a dongle
11016 3 has taken a dongle
11035 25 has taken a dongle
11036 22 has taken a dongle
11038 31 has taken a dongle
11069 13 has taken a dongle
11086 38 is refactoring
11088 17 has taken a dongle
11089 37 has taken a dongle
11112 27 has taken a dongle
11120 35 has taken a dongle
11122 41 is compiling
11123 19 has taken a dongle
11126 29 has taken a dongle
11128 1 has taken a dongle
11129 7 has taken a dongle
11131 15 has taken a dongle
11133 45 has taken a dongle
11134 33 has taken a dongle
11136 9 has taken a dongle
11137 43 has taken a dongle
11139 49 has taken a dongle
11141 11 has taken a dongle
11142 25 is compiling
11178 3 has taken a dongle
11188 22 is compiling
11189 7 is compiling
11191 13 is compiling
11193 37 has taken a dongle
11195 17 is compiling
11198 35 is compiling
11276 19 is compiling
11277 33 is compiling
11279 1 is compiling
11280 43 is compiling
11289 27 has taken a dongle
11292 45 is compiling
11293 15 is compiling
11294 11 is compiling
11297 31 is compiling
11299 49 is compiling
11302 3 is compiling
11328 9 is compiling
11345 29 is compiling
11348 37 is compiling
11353 27 is compiling
11405 13 is debugging
11453 41 is debugging
11459 17 is debugging
11504 22 is debugging
11538 25 is debugging
11645 35 is debugging
11652 1 is debugging
11654 7 is debugging
11656 15 is debugging
11658 13 is refactoring
11659 27 is debugging
11711 41 is refactoring
11716 17 is refactoring
11718 31 is debugging
11719 19 is debugging
11724 33 is debugging
11726 49 is debugging
11728 9 is debugging
11732 29 is debugging
11734 22 is refactoring
11744 45 is debugging
12009 3 is debugging
12053 25 is refactoring
12055 43 is debugging
12056 37 is debugging
12058 35 is refactoring
12086 1 is refactoring
12087 7 is refactoring
12089 15 is refactoring
12090 27 is refactoring
12091 31 is refactoring
12092 19 is refactoring
12093 49 is refactoring
12094 33 is refactoring
12148 9 is refactoring
12150 29 is refactoring
12187 11 is debugging
12188 4 burned out

## Testing with 50 Coders, Burnout! FIFO

valgrind --tool=helgrind ./Codexion 50 100 200 200 200 3 100 fifo 2> dbm/debugging_50bf.txt


110 1 burned out

## Testing with 50 Coders, Burnout! EDF

valgrind --tool=helgrind ./Codexion 50 100 200 200 200 3 100 edf 2> dbm/debugging_50be.txt


123 35 has taken a dongle
127 35 has taken a dongle
130 35 is compiling
184 31 has taken a dongle
286 47 has taken a dongle
296 1 has taken a dongle
311 1 has taken a dongle
312 1 is compiling
328 37 has taken a dongle
329 37 has taken a dongle
330 37 is compiling
332 9 has taken a dongle
364 33 has taken a dongle
367 21 has taken a dongle
368 29 has taken a dongle
374 39 has taken a dongle
375 7 has taken a dongle
377 17 has taken a dongle
378 15 has taken a dongle
379 49 has taken a dongle
380 23 has taken a dongle
382 11 has taken a dongle
383 13 has taken a dongle
385 47 has taken a dongle
386 3 has taken a dongle
388 27 has taken a dongle
390 31 has taken a dongle
391 1 burned out

# Testing 100

## Testing with 100 Coders, no Burnout FIFO

valgrind --tool=helgrind ./Codexion 100 15000 200 200 200 3 100 fifo 2> dbm/debugging_100sf.txt


1574 69 has taken a dongle
1597 69 has taken a dongle
2047 47 has taken a dongle
2418 71 has taken a dongle
2421 17 has taken a dongle
2423 69 is compiling
3018 98 has taken a dongle
3128 32 has taken a dongle
3143 43 has taken a dongle
4493 41 has taken a dongle
4568 74 has taken a dongle
4993 41 has taken a dongle
5006 77 has taken a dongle
5068 87 has taken a dongle
5083 63 has taken a dongle
5086 47 has taken a dongle
5677 71 has taken a dongle
5680 17 has taken a dongle
5682 15 has taken a dongle
5786 50 has taken a dongle
5788 79 has taken a dongle
5790 83 has taken a dongle
6064 95 has taken a dongle
6158 22 has taken a dongle
6225 57 has taken a dongle
6416 66 has taken a dongle
6425 93 has taken a dongle
6428 91 has taken a dongle
6486 13 has taken a dongle
6487 19 has taken a dongle
6742 5 has taken a dongle
6793 32 has taken a dongle
6810 27 has taken a dongle
6812 54 has taken a dongle
6938 11 has taken a dongle
6939 98 has taken a dongle
6941 25 has taken a dongle
6943 35 has taken a dongle
6944 3 has taken a dongle
6946 60 has taken a dongle
6947 37 has taken a dongle
6949 69 is debugging
6988 74 has taken a dongle
6989 41 is compiling
6991 77 has taken a dongle
6995 29 has taken a dongle
6997 87 has taken a dongle
7000 63 has taken a dongle
7000 8 has taken a dongle
7013 68 has taken a dongle
7162 39 has taken a dongle
7164 43 has taken a dongle
7166 47 is compiling
7168 17 is compiling
7173 71 is compiling
7175 15 has taken a dongle
7181 50 has taken a dongle
7182 79 has taken a dongle
7184 83 has taken a dongle
7186 95 has taken a dongle
7187 57 has taken a dongle
7189 22 has taken a dongle
7264 93 has taken a dongle
7266 66 has taken a dongle
7292 13 has taken a dongle
7296 91 has taken a dongle
7331 5 has taken a dongle
7459 19 has taken a dongle
7461 32 is compiling
7561 25 has taken a dongle
7562 19 is compiling
7579 11 has taken a dongle
7580 60 has taken a dongle
7582 54 has taken a dongle
7584 98 is compiling
7586 3 has taken a dongle
7596 37 has taken a dongle
7598 8 has taken a dongle
7600 27 has taken a dongle
7620 69 is refactoring
7731 77 is compiling
8028 57 is compiling
8030 29 has taken a dongle
8096 87 is compiling
8232 15 is compiling
8234 74 is compiling
8236 79 is compiling
8238 68 has taken a dongle
8239 95 is compiling
8242 22 is compiling
8244 66 is compiling
8245 13 is compiling
8248 83 is compiling
8250 63 is compiling
8252 50 is compiling
8336 91 is compiling
8338 39 has taken a dongle
8340 71 is debugging
8344 48 has taken a dongle
8348 93 is compiling
8439 5 is compiling
8441 35 has taken a dongle
8535 43 is compiling
8631 35 is compiling
8634 25 is compiling
8636 41 is debugging
8639 8 is compiling
8642 54 is compiling
8665 3 is compiling
8743 11 is compiling
8744 60 is compiling
8748 27 is compiling
8749 70 has taken a dongle
8836 98 is debugging
8838 17 is debugging
8841 97 has taken a dongle
8919 18 has taken a dongle
8997 19 is debugging
8999 29 is compiling
9001 32 is debugging
9003 37 is compiling
9005 57 is debugging
9006 68 is compiling
9102 56 has taken a dongle
9120 83 is debugging
9122 48 has taken a dongle
9123 71 is refactoring
9126 15 is debugging
9128 87 is debugging
9130 39 is compiling
9132 58 has taken a dongle
9135 74 is debugging
9136 47 is debugging
9199 91 is debugging
9207 32 is refactoring
9213 16 has taken a dongle
9214 5 is debugging
10680 13 is debugging
12376 95 is debugging
12968 86 has taken a dongle
12970 66 is debugging
12971 41 is refactoring
12973 79 is debugging
12974 14 has taken a dongle
12976 84 has taken a dongle
12979 73 has taken a dongle
12980 22 is debugging
12981 76 has taken a dongle
12982 90 has taken a dongle
12984 70 has taken a dongle
12985 35 is debugging
12987 63 is debugging
12989 97 has taken a dongle
12990 98 is refactoring
12991 17 is refactoring
13000 60 is debugging
13001 18 has taken a dongle
13003 78 has taken a dongle
13004 27 is debugging
13021 4 has taken a dongle
13022 51 has taken a dongle
13023 43 is debugging
13025 3 is debugging
13027 58 has taken a dongle
13028 56 has taken a dongle
13030 62 has taken a dongle
13032 19 is refactoring
13033 57 is refactoring
13035 77 is debugging
13037 93 is debugging
13038 8 is debugging
13039 50 is debugging
13041 26 has taken a dongle
13044 44 has taken a dongle
13045 83 is refactoring
13047 15 is refactoring
13049 87 is refactoring
13050 74 is refactoring
13052 2 has taken a dongle
13053 37 is debugging
13054 21 has taken a dongle
13056 16 has taken a dongle
13057 47 is refactoring
13095 91 is refactoring
13097 42 has taken a dongle
13099 7 has taken a dongle
13100 68 is debugging
13102 64 has taken a dongle
13103 29 is debugging
13105 5 is refactoring
13107 54 is debugging
13109 25 is debugging
13110 92 has taken a dongle
13112 36 has taken a dongle
13113 94 has taken a dongle
13115 12 has taken a dongle
13116 13 is refactoring
13118 28 has taken a dongle
13120 39 is debugging
13121 48 is compiling
13123 67 has taken a dongle
13127 11 is debugging
13129 38 has taken a dongle
13130 34 has taken a dongle
13132 86 has taken a dongle
13134 70 is compiling
13135 84 has taken a dongle
13137 14 has taken a dongle
13139 24 has taken a dongle
13142 18 is compiling
13144 73 has taken a dongle
13145 26 has taken a dongle
13184 44 has taken a dongle
13186 2 has taken a dongle
13189 40 has taken a dongle
13200 9 has taken a dongle
13442 21 has taken a dongle
13444 16 is compiling
13446 78 has taken a dongle
13480 4 has taken a dongle
13483 58 is compiling
13485 56 is compiling
13489 90 has taken a dongle
13491 97 is compiling
13494 76 has taken a dongle
13497 64 has taken a dongle
13529 67 has taken a dongle
13531 38 has taken a dongle
13533 34 has taken a dongle
13537 82 has taken a dongle
13610 51 has taken a dongle
13972 51 is compiling
14074 79 is refactoring
14076 95 is refactoring
14079 22 is refactoring
14080 36 has taken a dongle
14082 94 has taken a dongle
14084 14 is compiling
14176 24 has taken a dongle
14177 35 is refactoring
14192 63 is refactoring
14194 86 is compiling
14196 60 is refactoring
14198 84 is compiling
14201 12 has taken a dongle
14202 26 is compiling
14204 27 is refactoring
14206 43 is refactoring
14208 3 is refactoring
14304 77 is refactoring
14443 93 is refactoring
14445 8 is refactoring
14448 50 is refactoring
14450 37 is refactoring
14452 7 has taken a dongle
14453 28 has taken a dongle
14455 40 has taken a dongle
14457 68 is refactoring
14460 29 is refactoring
14461 54 is refactoring
14579 25 is refactoring
14581 39 is refactoring
14583 73 is compiling
14585 11 is refactoring
14588 2 is compiling
14590 44 is compiling
14591 42 has taken a dongle
14593 76 is compiling
14596 78 is compiling
14599 34 is compiling
14602 67 is compiling
14628 82 has taken a dongle
14630 49 has taken a dongle
14631 64 is compiling
14867 21 is compiling
15008 38 is compiling
15010 62 has taken a dongle
15012 4 is compiling
15013 30 has taken a dongle
15015 90 is compiling
15018 48 is debugging
15218 9 has taken a dongle
15220 92 has taken a dongle
15223 58 is debugging
15226 18 is debugging
15227 66 is refactoring
15516 16 is debugging
15520 59 has taken a dongle
15523 70 is debugging
15546 56 is debugging
15548 17 has taken a dongle
15616 94 is compiling
15618 24 is compiling
15622 69 has taken a dongle
15623 12 is compiling
15626 57 has taken a dongle
15629 55 has taken a dongle
15631 51 is debugging
15633 26 is debugging
15635 96 has taken a dongle
15637 7 is compiling
15639 36 is compiling
15641 28 is compiling
15644 86 is debugging
15646 97 is debugging
15649 40 is compiling
15651 14 is debugging
15653 84 is debugging
15655 1 burned out

## Testing with 100 Coders, no Burnout EDF

valgrind --tool=helgrind ./Codexion 100 15000 200 200 200 3 100 edf 2> dbm/debugging_100se.txt


124 21 has taken a dongle
129 21 has taken a dongle
134 21 is compiling
693 11 has taken a dongle
695 87 has taken a dongle
2685 75 has taken a dongle
2688 49 has taken a dongle
2690 81 has taken a dongle
2820 71 has taken a dongle
2822 51 has taken a dongle
2824 97 has taken a dongle
2826 33 has taken a dongle
2828 41 has taken a dongle
3477 99 has taken a dongle
4246 57 has taken a dongle
5144 85 has taken a dongle
5205 11 has taken a dongle
6052 2 has taken a dongle
7040 13 has taken a dongle
7224 39 has taken a dongle
7225 61 has taken a dongle
7226 67 has taken a dongle
7257 47 has taken a dongle
7258 69 has taken a dongle
7260 73 has taken a dongle
7262 15 has taken a dongle
7263 59 has taken a dongle
7308 44 has taken a dongle
7310 29 has taken a dongle
7312 36 has taken a dongle
7616 31 has taken a dongle
7674 91 has taken a dongle
7677 53 has taken a dongle
7767 19 has taken a dongle
7804 53 has taken a dongle
7807 93 has taken a dongle
7887 9 has taken a dongle
7908 49 has taken a dongle
7909 79 has taken a dongle
8101 77 has taken a dongle
8173 25 has taken a dongle
8208 21 is debugging
8210 87 has taken a dongle
8212 63 has taken a dongle
8213 51 has taken a dongle
8215 99 has taken a dongle
8217 81 has taken a dongle
8218 71 has taken a dongle
8220 97 has taken a dongle
8221 41 has taken a dongle
8335 7 has taken a dongle
8408 57 has taken a dongle
8409 55 has taken a dongle
8412 5 has taken a dongle
8414 85 has taken a dongle
8473 23 has taken a dongle
8475 11 is compiling
8477 2 has taken a dongle
8486 33 has taken a dongle
8517 15 has taken a dongle
8519 39 has taken a dongle
8520 67 has taken a dongle
8522 13 has taken a dongle
8540 69 has taken a dongle
8622 61 has taken a dongle
8624 29 has taken a dongle
8627 73 has taken a dongle
8628 59 has taken a dongle
8631 44 has taken a dongle
8633 47 has taken a dongle
8635 36 has taken a dongle
8636 31 has taken a dongle
8639 91 has taken a dongle
8667 75 has taken a dongle
8669 19 has taken a dongle
8773 93 has taken a dongle
8775 49 is compiling
8777 9 has taken a dongle
8779 53 is compiling
8782 79 has taken a dongle
8784 77 has taken a dongle
8786 87 is compiling
8990 81 is compiling
8992 63 has taken a dongle
8994 99 is compiling
8996 71 is compiling
8998 51 is compiling
9000 25 has taken a dongle
9002 97 is compiling
9059 21 is refactoring
9061 25 is compiling
9063 7 has taken a dongle
9065 41 is compiling
9066 57 is compiling
9162 55 has taken a dongle
9164 85 is compiling
9166 2 is compiling
9168 23 has taken a dongle
9170 39 is compiling
9173 15 is compiling
9180 33 is compiling
9182 61 is compiling
9183 47 is compiling
9200 31 is compiling
9278 67 is compiling
9280 44 is compiling
9283 75 is compiling
9288 59 is compiling
9290 69 is compiling
9292 73 is compiling
9307 13 is compiling
9386 36 is compiling
9420 99 is debugging
9525 9 is compiling
9527 91 is compiling
9530 19 is compiling
9566 11 is debugging
9568 79 is compiling
9594 49 is debugging
9596 53 is debugging
9598 77 is compiling
9600 29 is compiling
9696 63 is compiling
10079 5 has taken a dongle
10081 7 is compiling
10112 23 is compiling
10115 55 is compiling
10194 81 is debugging
10214 87 is debugging
10217 61 is debugging
10220 93 is compiling
10222 47 is debugging
10225 51 is debugging
10276 85 is debugging
10278 67 is debugging
10296 2 is debugging
10323 41 is debugging
10325 71 is debugging
10334 25 is debugging
10353 57 is debugging
10355 69 is debugging
10357 39 is debugging
10359 99 is refactoring
10361 73 is debugging
10363 19 is debugging
10365 11 is refactoring
10366 53 is refactoring
10368 49 is refactoring
10369 79 is debugging
10371 13 is debugging
10374 98 has taken a dongle
10376 91 is debugging
10378 3 has taken a dongle
10379 52 has taken a dongle
10397 48 has taken a dongle
10411 82 has taken a dongle
10413 40 has taken a dongle
10415 1 has taken a dongle
10417 15 is debugging
10458 50 has taken a dongle
10461 58 has taken a dongle
10462 84 has taken a dongle
10476 26 has taken a dongle
10538 86 has taken a dongle
10577 97 is debugging
10580 70 has taken a dongle
10582 59 is debugging
10640 18 has taken a dongle
10657 9 is debugging
10660 96 has taken a dongle
10662 72 has taken a dongle
10667 5 is compiling
10672 46 has taken a dongle
10685 68 has taken a dongle
10687 33 is debugging
10701 75 is debugging
10704 60 has taken a dongle
10718 90 has taken a dongle
10720 74 has taken a dongle
11694 12 has taken a dongle
12414 37 has taken a dongle
12429 16 has taken a dongle
12459 10 has taken a dongle
13013 31 is debugging
13691 77 is debugging
13723 78 has taken a dongle
13937 44 is debugging
14781 32 has taken a dongle
14783 66 has taken a dongle
14798 36 is debugging
14957 76 has taken a dongle
14959 34 has taken a dongle
15163 7 is debugging
15165 14 has taken a dongle
15167 63 is debugging
15169 23 is debugging
15177 3 has taken a dongle
15192 98 has taken a dongle
15195 20 has taken a dongle
15197 20 has taken a dongle
15199 80 has taken a dongle
15201 29 is debugging
15532 43 has taken a dongle
15574 81 is refactoring
15613 55 is debugging
15758 87 is refactoring
15805 61 is refactoring
15847 82 has taken a dongle
15849 40 has taken a dongle
15851 1 has taken a dongle
15853 47 is refactoring
15855 8 has taken a dongle
15856 50 has taken a dongle
15859 51 is refactoring
15861 85 is refactoring
15875 67 is refactoring
15877 24 has taken a dongle
15879 54 has taken a dongle
15881 30 has taken a dongle
15916 2 is refactoring
15918 41 is refactoring
15920 71 is refactoring
15922 84 has taken a dongle
15961 48 has taken a dongle
15963 25 is refactoring
15991 57 is refactoring
16004 69 is refactoring
16008 39 is refactoring
16049 73 is refactoring
16050 19 is refactoring
16052 79 is refactoring
16054 13 is refactoring
16058 64 has taken a dongle
16079 91 is refactoring
16081 93 is debugging
16084 70 has taken a dongle
16085 58 has taken a dongle
16087 86 has taken a dongle
16090 22 has taken a dongle
16094 94 has taken a dongle
16139 92 has taken a dongle
16156 26 has taken a dongle
16158 56 has taken a dongle
16247 15 is refactoring
16255 62 has taken a dongle
16258 46 has taken a dongle
16267 97 is refactoring
16270 59 is refactoring
16271 9 is refactoring
16273 33 is refactoring
16276 75 is refactoring
16279 5 is debugging
16339 72 has taken a dongle
16343 68 has taken a dongle
16345 96 has taken a dongle
16347 90 has taken a dongle
16372 18 has taken a dongle
16428 12 has taken a dongle
16608 60 has taken a dongle
16610 45 has taken a dongle
16612 6 has taken a dongle
16614 6 has taken a dongle
16619 16 has taken a dongle
16634 10 has taken a dongle
16639 31 is refactoring
16667 12 is compiling
16669 16 is compiling
16681 10 is compiling
16688 78 has taken a dongle
16693 78 is compiling
16696 32 has taken a dongle
16697 37 has taken a dongle
16702 66 has taken a dongle
16711 76 has taken a dongle
16717 76 is compiling
16725 1 burned out

## Testing with 100 Coders, no Burnout FIFO, long cooldown

valgrind --tool=helgrind ./Codexion 100 15000 200 200 200 3 1000 fifo 2> dbm/debugging_100lf.txt


1103 60 has taken a dongle
3748 72 has taken a dongle
4345 99 has taken a dongle
4348 80 has taken a dongle
4464 87 has taken a dongle
4467 15 has taken a dongle
4494 47 has taken a dongle
4496 42 has taken a dongle
4508 85 has taken a dongle
7281 55 has taken a dongle
7310 69 has taken a dongle
7311 57 has taken a dongle
7312 13 has taken a dongle
7325 97 has taken a dongle
7327 60 has taken a dongle
7329 37 has taken a dongle
7342 25 has taken a dongle
7344 99 has taken a dongle
7659 7 has taken a dongle
7703 80 has taken a dongle
7714 39 has taken a dongle
7716 63 has taken a dongle
7718 32 has taken a dongle
7758 20 has taken a dongle
7778 44 has taken a dongle
7818 87 has taken a dongle
7821 83 has taken a dongle
7823 94 has taken a dongle
7824 23 has taken a dongle
7826 10 has taken a dongle
7828 51 has taken a dongle
7829 47 has taken a dongle
7831 72 has taken a dongle
7833 4 has taken a dongle
7835 75 has taken a dongle
7836 89 has taken a dongle
7838 15 has taken a dongle
7840 69 has taken a dongle
7841 57 has taken a dongle
7843 97 has taken a dongle
7845 2 has taken a dongle
7847 55 has taken a dongle
7849 37 has taken a dongle
7850 25 has taken a dongle
7851 17 has taken a dongle
7853 85 has taken a dongle
7855 66 has taken a dongle
7856 13 has taken a dongle
7858 35 has taken a dongle
7860 42 has taken a dongle
7862 60 is compiling
7865 7 has taken a dongle
7869 28 has taken a dongle
7870 99 is compiling
7873 20 has taken a dongle
7874 80 is compiling
7877 32 has taken a dongle
7880 87 is compiling
7882 63 has taken a dongle
7886 15 is compiling
7888 55 is compiling
7903 89 has taken a dongle
8034 10 has taken a dongle
8036 44 has taken a dongle
8073 7 is compiling
8075 28 has taken a dongle
8078 37 is compiling
8169 32 is compiling
8173 4 has taken a dongle
8210 63 is compiling
8212 13 is compiling
8214 51 has taken a dongle
8215 42 is compiling
8217 2 has taken a dongle
8218 25 is compiling
8220 75 has taken a dongle
8221 66 has taken a dongle
8223 39 has taken a dongle
8225 85 is compiling
8226 57 is compiling
8229 97 is compiling
8230 83 has taken a dongle
8319 17 has taken a dongle
8323 94 has taken a dongle
8408 23 has taken a dongle
8411 10 is compiling
8413 69 is compiling
8416 72 is compiling
8418 20 is compiling
8419 89 is compiling
8441 28 is compiling
8442 35 has taken a dongle
8444 15 is debugging
8447 80 is debugging
8449 55 is debugging
8451 60 is debugging
8453 99 is debugging
8455 47 is compiling
8458 44 is compiling
8460 51 is compiling
8508 4 is compiling
8510 87 is debugging
8512 66 is compiling
8514 75 is compiling
8515 2 is compiling
8516 39 is compiling
8518 17 is compiling
8519 83 is compiling
8523 7 is debugging
8525 94 is compiling
8527 23 is compiling
8540 35 is compiling
8543 97 is debugging
8553 32 is debugging
8555 63 is debugging
8633 42 is debugging
8714 85 is debugging
8730 13 is debugging
8894 37 is debugging
8897 57 is debugging
9021 15 is refactoring
9023 80 is refactoring
10184 25 is debugging
10188 55 is refactoring
11038 60 is refactoring
11499 99 is refactoring
11502 10 is debugging
11526 44 is debugging
11529 89 is debugging
11547 87 is refactoring
11548 7 is refactoring
11567 69 is debugging
11786 72 is debugging
11788 97 is refactoring
11883 32 is refactoring
11885 63 is refactoring
11887 28 is debugging
11900 42 is refactoring
11901 85 is refactoring
11919 83 is debugging
11932 20 is debugging
11934 23 is debugging
11948 75 is debugging
12277 94 is debugging
12293 2 is debugging
13424 47 is debugging
13454 35 is debugging
13603 39 is debugging
14185 13 is refactoring
14458 37 is refactoring
14805 17 is debugging
14808 51 is debugging
15122 79 has taken a dongle
15125 66 is debugging
15127 61 has taken a dongle
15128 57 is refactoring
15133 8 has taken a dongle
15134 4 is debugging
15179 86 has taken a dongle
15182 41 has taken a dongle
15186 41 has taken a dongle
15187 25 is refactoring
15210 3 has taken a dongle
15240 45 has taken a dongle
15243 45 has taken a dongle
15244 93 has taken a dongle
15248 98 has taken a dongle
15270 27 has taken a dongle
15362 18 has taken a dongle
15364 71 has taken a dongle
15366 36 has taken a dongle
15368 56 has taken a dongle
15369 38 has taken a dongle
15371 1 has taken a dongle
15399 88 has taken a dongle
15402 90 has taken a dongle
15405 82 has taken a dongle
15451 24 has taken a dongle
15453 54 has taken a dongle
15455 43 has taken a dongle
15457 48 has taken a dongle
15458 76 has taken a dongle
15473 58 has taken a dongle
15474 34 has taken a dongle
15477 11 has taken a dongle
15513 74 has taken a dongle
15515 10 is refactoring
15517 44 is refactoring
15518 89 is refactoring
15521 95 has taken a dongle
15523 64 has taken a dongle
15524 69 is refactoring
15527 76 has taken a dongle
15615 84 has taken a dongle
15616 22 has taken a dongle
15618 28 is refactoring
15620 20 is refactoring
15622 23 is refactoring
15625 83 is refactoring
15628 75 is refactoring
15631 94 is refactoring
15656 67 has taken a dongle
15678 29 has taken a dongle
15680 5 has taken a dongle
15741 2 is refactoring
15743 47 is refactoring
15781 35 is refactoring
15802 39 is refactoring
15804 1 burned out

## Testing with 100 Coders, no Burnout EDF, long cooldown

valgrind --tool=helgrind ./Codexion 100 15000 200 200 200 3 1000 edf 2> dbm/debugging_100le.txt


848 75 has taken a dongle
5083 30 has taken a dongle
5101 11 has taken a dongle
7003 98 has taken a dongle
7005 95 has taken a dongle
7028 36 has taken a dongle
7913 82 has taken a dongle
8273 38 has taken a dongle
8285 84 has taken a dongle
8300 23 has taken a dongle
8606 73 has taken a dongle
8627 30 has taken a dongle
8628 91 has taken a dongle
8630 54 has taken a dongle
8653 50 has taken a dongle
8655 88 has taken a dongle
8698 7 has taken a dongle
8700 64 has taken a dongle
8711 9 has taken a dongle
8824 95 has taken a dongle
8826 52 has taken a dongle
8828 57 has taken a dongle
8830 11 has taken a dongle
8831 98 has taken a dongle
8833 36 has taken a dongle
8835 75 has taken a dongle
8836 84 has taken a dongle
8838 14 has taken a dongle
8840 66 has taken a dongle
8841 41 has taken a dongle
8842 38 has taken a dongle
8844 70 has taken a dongle
8846 25 has taken a dongle
8849 33 has taken a dongle
8954 30 is compiling
8981 91 has taken a dongle
9010 16 has taken a dongle
9011 50 has taken a dongle
9041 88 has taken a dongle
9044 64 has taken a dongle
9110 23 has taken a dongle
9112 25 has taken a dongle
9114 52 has taken a dongle
9116 20 has taken a dongle
9118 36 is compiling
9119 84 is compiling
9123 38 is compiling
9126 82 has taken a dongle
9141 57 has taken a dongle
9874 54 has taken a dongle
9929 66 has taken a dongle
10044 95 is compiling
10057 14 has taken a dongle
10060 75 is compiling
10063 41 has taken a dongle
10079 9 has taken a dongle
10082 11 is compiling
10134 79 has taken a dongle
10143 33 has taken a dongle
10259 47 has taken a dongle
10528 7 has taken a dongle
10530 61 has taken a dongle
10584 18 has taken a dongle
10587 70 has taken a dongle
10589 98 is compiling
10592 43 has taken a dongle
10594 73 has taken a dongle
10596 88 is compiling
10598 1 has taken a dongle
10600 16 has taken a dongle
10602 82 is compiling
10861 23 is compiling
10866 50 is compiling
10869 38 is debugging
10907 91 is compiling
10936 25 is compiling
10993 36 is debugging
10995 64 is compiling
11019 52 is compiling
11190 20 has taken a dongle
11256 30 is debugging
11258 57 is compiling
11333 84 is debugging
11352 66 is compiling
11354 54 is compiling
11372 41 is compiling
11374 79 has taken a dongle
11376 33 is compiling
11378 14 is compiling
11380 9 is compiling
11382 11 is debugging
11443 18 has taken a dongle
11446 18 is compiling
11449 75 is debugging
11451 7 is compiling
11885 1 has taken a dongle
11901 95 is debugging
11904 73 is compiling
11945 16 is compiling
11947 61 has taken a dongle
11950 70 is compiling
11952 35 has taken a dongle
11955 43 has taken a dongle
12090 47 has taken a dongle
12093 88 is debugging
12095 37 has taken a dongle
12097 98 is debugging
12105 38 is refactoring
12325 50 is debugging
12327 36 is refactoring
12329 82 is debugging
12331 29 has taken a dongle
12334 20 is compiling
12336 25 is debugging
12353 91 is debugging
12356 23 is debugging
12428 30 is refactoring
12491 79 is compiling
12543 52 is debugging
12545 84 is refactoring
12547 11 is refactoring
12551 12 has taken a dongle
12553 66 is debugging
12555 75 is refactoring
12562 33 is debugging
12567 18 is debugging
12687 54 is debugging
12689 64 is debugging
12752 41 is debugging
12753 35 has taken a dongle
12755 66 is refactoring
12757 1 is compiling
12759 95 is refactoring
12764 61 is compiling
12775 47 is compiling
12776 7 is debugging
12781 57 is debugging
13509 37 has taken a dongle
13511 83 has taken a dongle
13513 9 is debugging
13516 3 has taken a dongle
13519 88 is refactoring
13521 98 is refactoring
13525 87 has taken a dongle
13528 26 has taken a dongle
13530 97 has taken a dongle
13535 29 has taken a dongle
13536 73 is debugging
13538 81 has taken a dongle
13540 82 is refactoring
13542 50 is refactoring
13544 25 is refactoring
13546 91 is refactoring
13548 12 has taken a dongle
13552 16 is debugging
13553 76 has taken a dongle
13555 51 has taken a dongle
13557 24 has taken a dongle
13559 23 is refactoring
13561 90 has taken a dongle
13563 43 is compiling
13740 52 is refactoring
13755 14 is debugging
14976 33 is refactoring
14978 67 has taken a dongle
14979 65 has taken a dongle
14981 18 is refactoring
14983 54 is refactoring
14984 64 is refactoring
14986 41 is refactoring
14988 92 has taken a dongle
14992 7 is refactoring
15533 55 has taken a dongle
15535 1 is debugging
15538 35 is compiling
15539 20 is debugging
15541 10 has taken a dongle
15543 32 has taken a dongle
15545 8 has taken a dongle
15612 53 has taken a dongle
15614 15 has taken a dongle
15616 70 is debugging
15618 97 has taken a dongle
15620 61 is debugging
15621 79 is debugging
15623 83 has taken a dongle
15625 37 is compiling
15627 12 is compiling
15628 51 has taken a dongle
15633 26 has taken a dongle
15739 90 has taken a dongle
15758 81 has taken a dongle
15760 47 is debugging
15766 3 has taken a dongle
15844 57 is refactoring
15846 9 is refactoring
15854 76 has taken a dongle
15858 87 has taken a dongle
15860 73 is refactoring
15862 16 is refactoring
15864 24 has taken a dongle
15865 69 has taken a dongle
15867 29 is compiling
15869 17 has taken a dongle
15872 6 has taken a dongle
15874 46 has taken a dongle
15876 19 has taken a dongle
15905 92 has taken a dongle
15907 67 has taken a dongle
15938 48 has taken a dongle
15939 65 has taken a dongle
15941 74 has taken a dongle
15943 60 has taken a dongle
15944 14 is refactoring
16078 40 has taken a dongle
16080 78 has taken a dongle
16083 100 has taken a dongle
16086 71 has taken a dongle
16188 43 is debugging
16191 21 has taken a dongle
16202 53 has taken a dongle
16204 55 has taken a dongle
16206 32 has taken a dongle
16208 8 has taken a dongle
16209 10 has taken a dongle
16211 26 is compiling
16272 1 is refactoring
16274 20 is refactoring
16275 15 has taken a dongle
16277 62 has taken a dongle
16279 90 is compiling
16281 83 is compiling
16289 81 is compiling
16331 51 is compiling
16333 61 is refactoring
16336 79 is refactoring
16338 70 is refactoring
16339 97 is compiling
16364 3 is compiling
16366 24 is compiling
16649 46 has taken a dongle
16651 87 is compiling
16653 19 has taken a dongle
16961 17 has taken a dongle
16963 6 has taken a dongle
16965 92 is compiling
16967 35 is debugging
16969 37 is debugging
16971 76 is compiling
16973 60 has taken a dongle
16975 67 is compiling
17004 48 has taken a dongle
17007 47 is refactoring
17009 74 has taken a dongle
17010 69 has taken a dongle
17012 12 is debugging
17035 65 is compiling
17061 78 has taken a dongle
17137 100 has taken a dongle
17139 40 has taken a dongle
17141 29 is debugging
17143 42 has taken a dongle
17153 10 is compiling
17268 32 is compiling
17270 71 has taken a dongle
17371 62 has taken a dongle
18473 55 is compiling
18475 21 has taken a dongle
18477 8 is compiling
18478 43 is refactoring
18488 53 is compiling
18597 15 is compiling
18601 90 is debugging
18605 59 has taken a dongle
18630 81 is debugging
18655 24 is debugging
18747 60 is compiling
18798 46 is compiling
18800 51 is debugging
18802 97 is debugging
18829 48 is compiling
18836 34 has taken a dongle
18838 17 is compiling
18842 36 has taken a dongle
18877 19 is compiling
18879 69 is compiling
18950 83 is debugging
18965 42 has taken a dongle
18984 6 is compiling
18986 35 is refactoring
18988 37 is refactoring
18990 87 is debugging
19011 12 is refactoring
19014 74 is compiling
19082 13 has taken a dongle
19084 40 is compiling
19086 29 is refactoring
19088 100 is compiling
19090 78 is compiling
19092 26 is debugging
19094 65 is debugging
19096 92 is debugging
19099 71 is compiling
19101 28 has taken a dongle
19102 80 has taken a dongle
19142 76 is debugging
19205 4 has taken a dongle
19241 2 has taken a dongle
19243 96 has taken a dongle
19245 32 is debugging
19248 82 has taken a dongle
19250 10 is debugging
19251 68 has taken a dongle
19263 67 is debugging
19274 89 has taken a dongle
19362 91 has taken a dongle
19366 77 has taken a dongle
19369 62 is compiling
19371 3 is debugging
19439 49 has taken a dongle
19440 21 is compiling
19443 25 has taken a dongle
19454 31 has taken a dongle
19456 59 has taken a dongle
19465 86 has taken a dongle
19467 39 has taken a dongle
19524 93 has taken a dongle
19528 90 is refactoring
19530 55 is debugging
19532 53 is debugging
19534 8 is debugging
19536 81 is refactoring
19541 34 has taken a dongle
19543 15 is debugging
19545 36 has taken a dongle
19570 66 has taken a dongle
19612 24 is refactoring
19615 51 is refactoring
19617 97 is refactoring
19619 42 is compiling
19620 11 has taken a dongle
19623 13 has taken a dongle
19625 17 is debugging
19626 28 has taken a dongle
19627 46 is debugging
19629 80 has taken a dongle
19632 72 has taken a dongle
19634 83 is refactoring
19638 87 is refactoring
19640 82 has taken a dongle
19643 2 has taken a dongle
19644 19 is debugging
19646 68 has taken a dongle
19647 26 is refactoring
19651 65 is refactoring
19653 92 is refactoring
19655 4 has taken a dongle
19657 74 is debugging
19659 76 is refactoring
19738 2 burned out

## Testing with 200 Coders, Burnout! FIFO

valgrind --tool=helgrind ./Codexion 200 100 200 200 200 3 100 fifo 2> dbm/debugging_200bf.txt


1365 1 burned out

## Testing with 200 Coders, Burnout! EDF

valgrind --tool=helgrind ./Codexion 200 100 200 200 200 3 100 edf 2> dbm/debugging_200be.txt


723 1 burned out

# Testing 200

## Testing with 200 Coders, no Burnout FIFO

valgrind --tool=helgrind ./Codexion 200 20000 200 200 200 3 100 fifo 2> dbm/debugging_200sf.txt


9028 197 has taken a dongle
23472 41 has taken a dongle
23479 131 has taken a dongle
23481 154 has taken a dongle
23676 8 has taken a dongle
23678 28 has taken a dongle
23681 127 has taken a dongle
23684 129 has taken a dongle
23686 53 has taken a dongle
23689 67 has taken a dongle
23691 122 has taken a dongle
23693 162 has taken a dongle
23694 44 has taken a dongle
23905 172 has taken a dongle
23907 193 has taken a dongle
23910 36 has taken a dongle
23920 58 has taken a dongle
23923 83 has taken a dongle
23927 158 has taken a dongle
23929 63 has taken a dongle
23932 6 has taken a dongle
23935 51 has taken a dongle
23938 10 has taken a dongle
23942 113 has taken a dongle
24108 1 burned out

## Testing with 200 Coders, no Burnout EDF

valgrind --tool=helgrind ./Codexion 200 20000 200 200 200 3 100 edf 2> dbm/debugging_200se.txt


5764 185 has taken a dongle
5884 185 has taken a dongle
11448 113 has taken a dongle
15015 64 has taken a dongle
20782 10 has taken a dongle
20815 119 has taken a dongle
22141 104 has taken a dongle
22145 165 has taken a dongle
22149 145 has taken a dongle
22183 159 has taken a dongle
22186 178 has taken a dongle
22188 121 has taken a dongle
22193 1 burned out

## Testing with 200 Coders, no Burnout FIFO, long cooldown

valgrind --tool=helgrind ./Codexion 200 20000 200 200 200 3 1000 fifo 2> dbm/debugging_200lf.txt


5056 82 has taken a dongle
20104 49 has taken a dongle
20109 194 has taken a dongle
20113 35 has taken a dongle
20117 1 has taken a dongle
20121 24 has taken a dongle
20124 141 has taken a dongle
20126 175 has taken a dongle
20129 162 has taken a dongle
20133 15 has taken a dongle
20137 93 has taken a dongle
20141 37 has taken a dongle
20144 96 has taken a dongle
20148 159 has taken a dongle
20153 173 has taken a dongle
20156 17 has taken a dongle
20159 13 has taken a dongle
20163 1 burned out

## Testing with 200 Coders, no Burnout EDF, long cooldown

valgrind --tool=helgrind ./Codexion 200 20000 200 200 200 3 1000 edf 2> dbm/debugging_200le.txt


6443 75 has taken a dongle
21097 159 has taken a dongle
22176 20 has taken a dongle
22181 77 has taken a dongle
22185 129 has taken a dongle
22420 9 has taken a dongle
22424 143 has taken a dongle
22432 103 has taken a dongle
23476 193 has taken a dongle
23478 163 has taken a dongle
23481 110 has taken a dongle
23484 175 has taken a dongle
23486 173 has taken a dongle
23489 124 has taken a dongle
23491 70 has taken a dongle
23494 113 has taken a dongle
23497 63 has taken a dongle
23500 121 has taken a dongle
23503 149 has taken a dongle
23506 22 has taken a dongle
23508 101 has taken a dongle
23511 147 has taken a dongle
23514 61 has taken a dongle
23517 67 has taken a dongle
23521 191 has taken a dongle
23525 25 has taken a dongle
23528 187 has taken a dongle
23530 115 has taken a dongle
24504 14 has taken a dongle
24508 27 has taken a dongle
24511 126 has taken a dongle
25379 95 has taken a dongle
25389 108 has taken a dongle
25793 136 has taken a dongle
25796 33 has taken a dongle
26667 73 has taken a dongle
26670 1 burned out

## Testing with 200 Coders, Burnout! FIFO

valgrind --tool=helgrind ./Codexion 200 100 200 200 200 3 100 fifo 2> dbm/debugging_200bf.txt


924 117 has taken a dongle
1965 130 has taken a dongle
1971 69 has taken a dongle
2386 79 has taken a dongle
2392 1 burned out

## Testing with 200 Coders, Burnout! EDF

valgrind --tool=helgrind ./Codexion 200 100 200 200 200 3 100 edf 2> dbm/debugging_200be.txt


1728 1 burned out
