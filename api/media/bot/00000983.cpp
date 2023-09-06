/**
 * This file is preprocessed by an obfuscator
 * to protect its copyright
 *
 * Please do not try to parse it
 * 
 * Obfuscator is written by Futrime<https://github.com/Futrime>
 */

#include "ai.h"

#include <iostream>

#include <stdlib.h>

#include <math.h>

#include <cstring>

#include <vector>

#include <queue>

using namespace std;
#define ZOMBIE_KIND 5

#define PLANT_KIND 6

#define TOTAL_TIME 2000

#define COLUMN 10

#define ROW 5

#define __obfs_cfcd208495d__ enum 
#define __obfs_c4ca42__ PlantType 
#define __obfs_c81e728d__ { 
#define __obfs_eccbc87e4b5ce2f__ NOPLANT 
#define __obfs_a87ff6__ = 
#define __obfs_e4da3b7fb__ 0, 
#define __obfs_16790__ SUNFLOWER, 
#define __obfs_8f14e45fceea16__ WINTERPEASHOOTER, 
#define __obfs_c9f0__ PEASHOOTER, 
#define __obfs_45__ SMALLNUT, 
#define __obfs_d3d9__ PEPPER, 
#define __obfs_6512bd43d9ca__ SQUASH 
#define __obfs_c20ad4d76__ }; 
#define __obfs_c51ce410c124a__ enum 
#define __obfs_aab3238922bcc25a__ ZombieType 
#define __obfs_9bf31c7ff06__ { 
#define __obfs_c74d97b01__ NOZOMBIE 
#define __obfs_70e__ = 
#define __obfs_6f492__ 0, 
#define __obfs_1f0e3d__ NORMAL, 
#define __obfs_98f1370__ BUCKET, 
#define __obfs_3c59dc048__ POLEVAULT, 
#define __obfs_b6d7__ SLED, 
#define __obfs_37693cfc748049e__ GARGANTUAR 
#define __obfs_1ff1de774005__ }; 
#define __obfs_8e296a067a3__ const 
#define __obfs_4e7__ int 
#define __obfs_02e74f__ plantCost[7] 
#define __obfs_33e75ff09dd__ = 
#define __obfs_6ea__ {0, 
#define __obfs_34173__ 50, 
#define __obfs_c16a5320fa4755__ 400, 
#define __obfs_6364d3f0f4__ 100, 
#define __obfs_182be0c__ 50, 
#define __obfs_e369853df76__ 125, 
#define __obfs_1c3__ 50}; 
#define __obfs_19ca14e7ea__ const 
#define __obfs_a5__ int 
#define __obfs_a5771bce93e200c__ plantCd[7] 
#define __obfs_d67d8ab4f4__ = 
#define __obfs_d645920__ {0, 
#define __obfs_3416a75f4ce__ 10, 
#define __obfs_a1d0c6e83f02__ 30, 
#define __obfs_17e62166__ 10, 
#define __obfs_f7177163__ 40, 
#define __obfs_6c8349cc7260__ 60, 
#define __obfs_d9d4f495e875__ 60}; 
#define __obfs_67c6__ const 
#define __obfs_642e92efb7942173__ int 
#define __obfs_f457c545a9__ zombieCost[6] 
#define __obfs_c0c7c__ = 
#define __obfs_28__ {0, 
#define __obfs_9a1158154dfa42c__ 50, 
#define __obfs_d82c8d161__ 125, 
#define __obfs_a684ece__ 125, 
#define __obfs_b53b3a3d6a__ 300, 
#define __obfs_9f61408e3afb63__ 300}; 
#define __obfs_72b3__ const 
#define __obfs_66f04__ int 
#define __obfs_093f65e080a29__ zombieCd[6] 
#define __obfs_072b030__ = 
#define __obfs_7f39f8__ {0, 
#define __obfs_44f683a84163__ 15, 
#define __obfs_03afdb__ 20, 
#define __obfs_ea5d2f1c460823__ 20, 
#define __obfs_fc490ca__ 25, 
#define __obfs_3295c76ac__ 25}; 
#define __obfs_735b90b456__ const 
#define __obfs_a3f39__ int 
#define __obfs_14bfa__ plantHp[7] 
#define __obfs_7cbbc409ec9__ = 
#define __obfs_e2c420d928d__ {0, 
#define __obfs_32b__ 300, 
#define __obfs_d2dd__ 300, 
#define __obfs_ad61ab1__ 300, 
#define __obfs_d09bf__ 4000, 
#define __obfs_fbd__ 0, 
#define __obfs_28dd__ 0}; 
#define __obfs_35f4a8__ const 
#define __obfs_d1f__ int 
#define __obfs_f033__ plantDps[7] 
#define __obfs_43ec517d6__ = 
#define __obfs_9778d5d__ {0, 
#define __obfs_fe9f__ 0, 
#define __obfs_68__ 20, 
#define __obfs_3ef815__ 10, 
#define __obfs_93db85ed9__ 0, 
#define __obfs_c7e1249ffc__ 0, 
#define __obfs_2a38a4a__ 0}; 
#define __obfs_7647966b7343__ int 
#define __obfs_861__ zombieHp[6] 
#define __obfs_54229a__ = 
#define __obfs_92cc227532__ {0, 
#define __obfs_98dce83da57__ 270, 
#define __obfs_f4b9ec30ad9f68f__ 820, 
#define __obfs_812b4ba287f5e__ 200, 
#define __obfs_26657d5ff9__ 1600, 
#define __obfs_e2ef524fbf3__ 3000}; 
#define __obfs_ed3d__ struct 
#define __obfs_ac627ab1ccbd__ Sunflower 
#define __obfs_f899139df5e105__ { 
#define __obfs_38__ int 
#define __obfs_ec8956637a997__ row, 
#define __obfs_6974ce5ac6__ column, 
#define __obfs_c9e1074f5b3__ cd; 
#define __obfs_65b9eea6e1__ Sunflower(int 
#define __obfs_f0935e4__ Row, 
#define __obfs_a97da629b098b75__ int 
#define __obfs_a3c65c__ Column) 
#define __obfs_2723d092b63885e__ { 
#define __obfs_5f93f983524d__ cd 
#define __obfs_698d51a__ = 
#define __obfs_7f6__ 24; 
#define __obfs_73278a4a__ row 
#define __obfs_5fd0b37cd7__ = 
#define __obfs_2b44928__ Row, 
#define __obfs_c45147d__ column 
#define __obfs_eb160de1de89d__ = 
#define __obfs_5ef059938ba799a__ Column; 
#define __obfs_07e1c__ } 
#define __obfs_da4fb5c__ }; 
#define __obfs_4c56ff4ce4aaf9__ int 
#define __obfs_a0a080f42e6f__ *zombieNum(int 
#define __obfs_202cb962ac5907__ ***zombies) 
#define __obfs_c8ffe9a587b12__ { 
#define __obfs_3def184ad8f4755f__ int 
#define __obfs_069059b7__ cnt[7] 
#define __obfs_ec5dec__ = 
#define __obfs_76dc611d6eba__ {}, 
#define __obfs_d1f491__ *p 
#define __obfs_9b8619251a19057__ = 
#define __obfs_1afa34a7f9__ cnt; 
#define __obfs_65ded5353__ for 
#define __obfs_9fc3d715__ (int 
#define __obfs_02__ i 
#define __obfs_7f1de29e6da__ = 
#define __obfs_42a0e188f__ 0; 
#define __obfs_3988c7f88ebcb58__ i 
#define __obfs_013d40716__ < 
#define __obfs_e00da__ 5; 
#define __obfs_1385974ed5904a43__ i++) 
#define __obfs_0f28__ for 
#define __obfs_a8ba__ (int 
#define __obfs_903ce9225__ j 
#define __obfs_0a09c8844ba8f__ = 
#define __obfs_2b2__ 0; 
#define __obfs_a5e00132373a703__ j 
#define __obfs_8d5e957f__ < 
#define __obfs_47d1e990583c9c__ 10; 
#define __obfs_f2217062__ j++) 
#define __obfs_7ef605fc__ for 
#define __obfs_a8f15eda8__ (int 
#define __obfs_37a749d808e4649__ k 
#define __obfs_b3e3e393c77e3__ = 
#define __obfs_1d7f7abc18fc__ 0; 
#define __obfs_2a79ea27__ k 
#define __obfs_1c9ac015__ < 
#define __obfs_6c4b761a28b734fe__ 10; 
#define __obfs_0640__ k++) 
#define __obfs_140f6969d5213fd__ { 
#define __obfs_b73ce398c39f50__ if 
#define __obfs_bd4c9ab730f5__ (zombies[i][j][k] 
#define __obfs_82__ = 
#define __obfs_0777d5c17d40__ -1) 
#define __obfs_fa7cdfa__ break; 
#define __obfs_9766__ else 
#define __obfs_7e7757b1e12__ cnt[zombies[i][j][k]]++; 
#define __obfs_5878a7ab8__ } 
#define __obfs_006f52e9102a8d3b__ return 
#define __obfs_3636638817772e__ p; 
#define __obfs_149e9677a5989fd3__ } 
#define __obfs_a4a042cf__ int 
#define __obfs_1ff__ *zombieNum(int 
#define __obfs_f7e6__ zombies[5][10][10]) 
#define __obfs_bf8229696f__ { 
#define __obfs_82161242827b7__ int 
#define __obfs_38af86134b__ cnt[7] 
#define __obfs_96da__ = 
#define __obfs_8f8551796__ {}, 
#define __obfs_8f53__ *p 
#define __obfs_0451__ = 
#define __obfs_fc221309746__ cnt; 
#define __obfs_4c5bde7__ for 
#define __obfs_cedebb6e87__ (int 
#define __obfs_6cdd60__ i 
#define __obfs_eecca5b63__ = 
#define __obfs_9872ed__ 0; 
#define __obfs_31fefc0e570cb38__ i 
#define __obfs_9d__ < 
#define __obfs_a2557a7b2e94197f__ 5; 
#define __obfs_cfecdb276__ i++) 
#define __obfs_0aa1883__ for 
#define __obfs_58a2fc6ed39fd08__ (int 
#define __obfs_bd686fd__ j 
#define __obfs_a597e50502f5__ = 
#define __obfs_0336dcb__ 0; 
#define __obfs_08__ j 
#define __obfs_85d8ce590ad__ < 
#define __obfs_0e6597__ 10; 
#define __obfs_84d9ee44e457dde__ j++) 
#define __obfs_3644a684__ for 
#define __obfs_757b505cfd34c64__ (int 
#define __obfs_854d6fae5ee42911__ k 
#define __obfs_e2c0b__ = 
#define __obfs_27__ 0; 
#define __obfs_eae27d7__ k 
#define __obfs_7e__ < 
#define __obfs_69__ 10; 
#define __obfs_091d584__ k++) 
#define __obfs_b1d10e7bafa44212__ { 
#define __obfs_6f3ef77ac0e36__ if 
#define __obfs_eb__ (zombies[i][j][k] 
#define __obfs_1534b76d__ = 
#define __obfs_979d472a848__ -1) 
#define __obfs_ca46c1b9512a__ break; 
#define __obfs_3b8a6142__ else 
#define __obfs_45f__ cnt[zombies[i][j][k]]++; 
#define __obfs_63dc__ } 
#define __obfs_e96__ return 
#define __obfs_c0e190d8267e3__ p; 
#define __obfs_ec8ce6a__ } 
#define __obfs_060ad92489947__ struct 
#define __obfs_bcbe3365e6ac95__ Zombie 
#define __obfs_115f89503138416__ { 
#define __obfs_13fe__ int 
#define __obfs_d1c38a09acc34__ num; 
#define __obfs_9cfdf10e8fc047a__ int 
#define __obfs_705f2172__ hp; 
#define __obfs_74db120f0a8e5646__ int 
#define __obfs_57aeee35c98205__ coX, 
#define __obfs_6da9003b743b6__ coY; 
#define __obfs_9b04d15__ Zombie(int 
#define __obfs_be83ab3ecd0db__ Num, 
#define __obfs_e165421110__ int 
#define __obfs_289dff07669d7a__ row) 
#define __obfs_577__ { 
#define __obfs_01161aaa0b6d13__ coX 
#define __obfs_539fd__ = 
#define __obfs_ac__ row, 
#define __obfs_555d67__ coY 
#define __obfs_335f5352088d7d9b__ = 
#define __obfs_f340f1b1f65__ 9; 
#define __obfs_e4a6222c__ hp 
#define __obfs_cb__ = 
#define __obfs_91__ zombieHp[Num]; 
#define __obfs_0266e33d3f546__ num 
#define __obfs_38d__ = 
#define __obfs_3cec07e9ba__ Num; 
#define __obfs_621bf66ddb7c9__ } 
#define __obfs_077e29b11be80a__ }; 
#define __obfs_6c9882bbac__ struct 
#define __obfs_19__ Plant 
#define __obfs_03c6__ { 
#define __obfs_c24cd76e1ce413__ int 
#define __obfs_c5__ num; 
#define __obfs_fe131__ int 
#define __obfs_f718499__ hp; 
#define __obfs_d96409bf89421768__ int 
#define __obfs_502e4a16930e41__ coX, 
#define __obfs_cfa0860e83a__ coY; 
#define __obfs_a4f23670e183__ int 
#define __obfs_b1a59b3__ dps; 
#define __obfs_36660e__ Plant(int 
#define __obfs_8c19f571e251__ Num, 
#define __obfs_d6baf65e0b240ce1__ int 
#define __obfs_e56__ row, 
#define __obfs_f7664060c__ int 
#define __obfs_eda80a3d5__ col) 
#define __obfs_8f121__ { 
#define __obfs_06138bc5af602364__ num 
#define __obfs_39059724__ = 
#define __obfs_7f1__ Num; 
#define __obfs_7a61__ coX 
#define __obfs_47__ = 
#define __obfs_d947bf0__ row, 
#define __obfs_63__ coY 
#define __obfs_db8__ = 
#define __obfs_20f07591c6fcb220__ col; 
#define __obfs_07c__ hp 
#define __obfs_d395771085__ = 
#define __obfs_92c8c96e4c371__ plantHp[Num]; 
#define __obfs_e3796ae__ dps 
#define __obfs_6a9aeddfc68__ = 
#define __obfs_0f49c89d1e72__ plantDps[Num]; 
#define __obfs_46ba9f2a69765__ } 
#define __obfs_0e01938__ }; 
#define __obfs_16a5cdae362b__ struct 
#define __obfs_918317b57931b6b7__ Actionlist 
#define __obfs_48aedb8880c__ { 
#define __obfs_839ab4682__ int 
#define __obfs_f90f2aca5__ plantPlace[5][10] 
#define __obfs_9c838d2e45b2ad__ = 
#define __obfs_1700002963a49da1__ {}, 
#define __obfs_53c3__ zombiePlace[5] 
#define __obfs_6883966f__ = 
#define __obfs_49182__ {}; 
#define __obfs_d296c101daa88a51__ int 
#define __obfs_9fd81843__ plantRemove[5][10] 
#define __obfs_26e359e83860db__ = 
#define __obfs_ef0d3930a7b6c95b__ {}; 
#define __obfs_94f6d7e04__ }; 
#define __obfs_34ed066df378e__ class 
#define __obfs_57__ Game 
#define __obfs_11b9842e0a27__ { 
#define __obfs_37bc__ public: 
#define __obfs_496e05e1aea0__ int 
#define __obfs_b2eb7__ time, 
#define __obfs_8e98__ sun, 
#define __obfs_a8c88a0055f__ moon; 
#define __obfs_eddea82ad2755b__ int 
#define __obfs_06eb61b__ plants[5][10], 
#define __obfs_9dfcd5e558dfa0__ zombies[5][10][10]; 
#define __obfs_950a__ int 
#define __obfs_158f3069a435b__ cdPlant[7], 
#define __obfs_758874998f__ cdZombie[6]; 
#define __obfs_ad1__ int 
#define __obfs_3fe94a002317b5f__ dps[5]; 
#define __obfs_5b8add2a5d9__ int 
#define __obfs_432a__ flagPlant[7], 
#define __obfs_8d3bba7425__ flagZombie[6]; 
#define __obfs_320__ int 
#define __obfs_caf1a3dfb__ flagShovel[5][10]; 
#define __obfs_5737c6ec2e071__ int 
#define __obfs_bc__ zombieCostPerRow[5]; 
#define __obfs_f2f__ vector<Sunflower> 
#define __obfs_89f0fd5__ sunFlowers; 
#define __obfs_a666587afda6e89a__ vector<Plant> 
#define __obfs_b83aac23b9528__ vectorPlants; 
#define __obfs_cd00692c3bfe592__ vector<Zombie> 
#define __obfs_6faa8040da2__ vectorZombies; 
#define __obfs_fe73f6__ void 
#define __obfs_6da37dd3139aa4__ plantremove(int 
#define __obfs_c0__ i, 
#define __obfs_310__ int 
#define __obfs_2f2b265625d76a__ j, 
#define __obfs_f9b9__ IPlayer 
#define __obfs_685545__ *player) 
#define __obfs_357a6fdf7642bf__ { 
#define __obfs_819f46e52c__ player->removePlant(i, 
#define __obfs_04025959b1__ j); 
#define __obfs_400__ flagShovel[i][j] 
#define __obfs_3dd48ab31d0__ = 
#define __obfs_58238e9ae2dd305d__ 1; 
#define __obfs_3ad7c2ebb9__ } 
#define __obfs_b3967a0e938dc2a6__ void 
#define __obfs_d81f__ maintain(IPlayer 
#define __obfs_13__ *player) 
#define __obfs_c5ff2543b53f4cc__ { 
#define __obfs_01386__ time++; 
#define __obfs_0bb4aec1__ int 
#define __obfs_9de6d14fff98__ **Plants 
#define __obfs_efe937780e9557__ = 
#define __obfs_371bc__ player->Camp->getCurrentPlants(); 
#define __obfs_138bb0696595__ int 
#define __obfs_8dd48d6a2e2cad__ ***Zombies 
#define __obfs_82ce__ = 
#define __obfs_6c524f__ player->Camp->getCurrentZombies(); 
#define __obfs_fb7b9ffa5462084c__ moon 
#define __obfs_aa__ += 
#define __obfs_c05__ int(time 
#define __obfs_e7b24b112a44fd__ / 
#define __obfs_52720e003547c__ 200.0) 
#define __obfs_c3e878e27f5__ + 
#define __obfs_00411460f7c92__ 1; 
#define __obfs_bac9162b4__ for 
#define __obfs_9be40cee5b0eee__ (int 
#define __obfs_5ef__ i 
#define __obfs_05049__ = 
#define __obfs_cf004fdc76__ 0; 
#define __obfs_0c74b7f78409a402__ i 
#define __obfs_d709f38ef75__ < 
#define __obfs_41f1f19176d38__ 5; 
#define __obfs_24b16fe__ i++) 
#define __obfs_ffd52f3c7e12435__ for 
#define __obfs_ad972f1__ (int 
#define __obfs_f61d6947467ccd3a__ j 
#define __obfs_142__ = 
#define __obfs_d34ab1__ 0; 
#define __obfs_8bf1211fd4__ j 
#define __obfs_a02f__ < 
#define __obfs_bca82e41ee__ 10; 
#define __obfs_00ec53c4__ j++) 
#define __obfs_4f6ffe1__ { 
#define __obfs_beed13602b9b0e6__ if 
#define __obfs_0584ce__ (plants[i][j] 
#define __obfs_dc__ > 
#define __obfs_39461a19e9e__ Plants[i][j] 
#define __obfs_8efb__ && 
#define __obfs_d9fc5b73a8d78fa__ plants[i][j] 
#define __obfs_c86a7ee__ != 
#define __obfs_a01a0380ca3c61__ PEPPER 
#define __obfs_5a4b25aaed25c__ && 
#define __obfs_f73b__ plants[i][j] 
#define __obfs_70c639df5__ != 
#define __obfs_28f0b864__ SQUASH) 
#define __obfs_1543843a4723ed__ { 
#define __obfs_f8c1f23d6a8d8d__ if 
#define __obfs_e46de7e1bca__ (flagShovel[i][j] 
#define __obfs_b7b16ecf8ca__ == 
#define __obfs_352fe25__ 1) 
#define __obfs_18d8__ { 
#define __obfs_816b112c6105b__ flagShovel[i][j] 
#define __obfs_69cb3ea317a32__ = 
#define __obfs_bbf94__ 0; 
#define __obfs_4f4adcbf8c6f6__ } 
#define __obfs_bbcbff5c__ else 
#define __obfs_8cb22bdd0b7__ { 
#define __obfs_f4f6dce2__ int 
#define __obfs_0d0fd7c6e093f7b8__ num 
#define __obfs_a96b__ = 
#define __obfs_1068c6e4c8051c__ plants[i][j]; 
#define __obfs_17d63b1625c8__ moon 
#define __obfs_b9228e096__ += 
#define __obfs_0d__ plantCost[num] 
#define __obfs_66808e327dc7__ / 
#define __obfs_42e7aaa88b48__ 5 
#define __obfs_8fe0093bb30d__ + 
#define __obfs_41ae__ int(sqrt(plantHp[num])); 
#define __obfs_d1f255a373a3ce__ dps[i] 
#define __obfs_7e___ -= 
#define __obfs_b6f0479__ plantDps[num]; 
#define __obfs_e0c641__ if 
#define __obfs_f8__ (num 
#define __obfs_faa9__ == 
#define __obfs_3c778__ 1) 
#define __obfs_25b2822c2f5a3__ { 
#define __obfs_6ecbd__ for 
#define __obfs_18997733ec258a9__ (int 
#define __obfs_8d7d__ k 
#define __obfs_75fc09__ = 
#define __obfs_f7490__ 0; 
#define __obfs_66368270f__ k 
#define __obfs_248e84433679__ < 
#define __obfs_019d385eb67__ sunFlowers.size(); 
#define __obfs_a49e9411d64f__ k++) 
#define __obfs_ddb306__ if 
#define __obfs_24__ (sunFlowers[k].row 
#define __obfs_fccb60__ == 
#define __obfs_1651cf0d__ i 
#define __obfs_eed5af6add9__ && 
#define __obfs_a8abb4bb284b5b27__ sunFlowers[k].column 
#define __obfs_15d4e891d7849__ == 
#define __obfs_c203d8a15161__ j) 
#define __obfs_13f3cf8c5319__ { 
#define __obfs_550a141f12de6__ sunFlowers.erase(sunFlowers.begin() 
#define __obfs_67f7fb873eaf2952__ + 
#define __obfs_1a5b1e4d__ k); 
#define __obfs_9a96__ break; 
#define __obfs_9b70e8__ } 
#define __obfs_d61e4bbd6__ } 
#define __obfs_f5f85__ } 
#define __obfs_941e1aaaba585__ } 
#define __obfs_9431c87f273e__ else 
#define __obfs_49__ if 
#define __obfs_e44fea__ (plants[i][j] 
#define __obfs_821fa7__ < 
#define __obfs_250cf8b51c77__ Plants[i][j]) 
#define __obfs_42998cf32d5__ { 
#define __obfs_d07e70efcfab0__ int 
#define __obfs_7fe1f8abaad094e__ num 
#define __obfs_98b2__ = 
#define __obfs_0353ab4cbed5__ Plants[i][j]; 
#define __obfs_51d92__ sun 
#define __obfs_428fc__ -= 
#define __obfs_f1b6f28__ plantCost[num]; 
#define __obfs_68ce199ec2c551__ dps[i] 
#define __obfs_e836d__ += 
#define __obfs_ab817c9349cf9c4f__ plantDps[num]; 
#define __obfs_877a9ba7a9__ cdPlant[num] 
#define __obfs_dc___ = 
#define __obfs_26337353b7962f53__ plantCd[num]; 
#define __obfs_8e6b42f1644ecb__ flagPlant[num] 
#define __obfs_ef575e__ = 
#define __obfs_2050e03__ 0; 
#define __obfs_25ddc0f8__ if 
#define __obfs_5ef0b4__ (num 
#define __obfs_598b3e71ec378bd__ == 
#define __obfs_7407__ 1) 
#define __obfs_cfee398643__ { 
#define __obfs_d18f65__ sun 
#define __obfs_6ea2ef7__ += 
#define __obfs_9461cce28ebe3e76__ 25; 
#define __obfs_f770__ sunFlowers.push_back(Sunflower(i, 
#define __obfs_e1__ j)); 
#define __obfs_eba0dc302bcd9a__ } 
#define __obfs_218a0__ vectorPlants.push_back(Plant(Plants[i][j], 
#define __obfs_7d04bbbe54__ i, 
#define __obfs_a516a87cfc__ j)); 
#define __obfs_c3c5__ } 
#define __obfs_854d9fc__ plants[i][j] 
#define __obfs_c410003__ = 
#define __obfs_559cb990c9dffd86__ Plants[i][j]; 
#define __obfs_55a7cf9c71f1c9c__ int 
#define __obfs_2f55707d4193d__ flag 
#define __obfs_1be3bc32e6__ = 
#define __obfs_35051070__ 0; 
#define __obfs_b534ba68__ for 
#define __obfs_738__ (int 
#define __obfs_05f971b5ec196b8__ k 
#define __obfs_3cf166c6b73f__ = 
#define __obfs_cee63__ 0; 
#define __obfs_5b69b9cb83__ k 
#define __obfs_b5b41__ < 
#define __obfs_285e__ vectorPlants.size(); 
#define __obfs_b337e84de8752__ k++) 
#define __obfs_e8c0653fea13f91__ { 
#define __obfs_ff4d5fbbafdf976c__ if 
#define __obfs_2d6cc__ (vectorPlants[k].coX 
#define __obfs_389bc7bb1e1c2a__ == 
#define __obfs_e2__ i 
#define __obfs_087__ && 
#define __obfs_a760880003e7dded__ vectorPlants[k].coY 
#define __obfs_10a7cdd970f__ == 
#define __obfs_3dc487__ j) 
#define __obfs_59__ { 
#define __obfs_2b8a6__ if 
#define __obfs_f3f27a__ (vectorPlants[k].num 
#define __obfs_38___ != 
#define __obfs_ebd9629__ Plants[i][j]) 
#define __obfs_63538fe6e__ { 
#define __obfs_cf67355a__ vectorPlants.erase(vectorPlants.begin() 
#define __obfs_07563a__ + 
#define __obfs_53fde96fcc4b4ce7__ k); 
#define __obfs_2bb232c0b1__ k--; 
#define __obfs_ba2fd31__ if 
#define __obfs_69421__ (Plants[i][j] 
#define __obfs_85__ != 
#define __obfs_13f320e7b5__ 0) 
#define __obfs_f4be00279e__ vectorPlants.push_back(Plant(Plants[i][j], 
#define __obfs_37f0e884fba__ i, 
#define __obfs_d64a340bcb633f5__ j)); 
#define __obfs_0fcbc61acd0__ } 
#define __obfs_298f95e1bf913__ flag 
#define __obfs_df877f3__ = 
#define __obfs_c399862d3b__ 1; 
#define __obfs_33__ break; 
#define __obfs_6565__ } 
#define __obfs_5ea1649a3133609__ } 
#define __obfs_7bcdf75ad237__ if 
#define __obfs_5737034557e__ (flag 
#define __obfs_9b72e31dac81__ == 
#define __obfs_16c222aa19__ 0 
#define __obfs_7dcd34__ && 
#define __obfs_814481__ Plants[i][j] 
#define __obfs_97e8527feaf77__ != 
#define __obfs_647bba34__ 0) 
#define __obfs_ed265__ vectorPlants.push_back(Plant(Plants[i][j], 
#define __obfs_c75b6f114c23a4d__ i, 
#define __obfs_8d342__ j)); 
#define __obfs_ccb1__ } 
#define __obfs_01f78be6f7cad02__ int 
#define __obfs_7f24d240521d9__ *z 
#define __obfs_94c7bb58efc__ = 
#define __obfs_f387624df__ zombieNum(zombies), 
#define __obfs_5e388103a391da__ *Z 
#define __obfs_15de21c670ae7c__ = 
#define __obfs_11b921ef__ zombieNum(Zombies); 
#define __obfs_6e2713a6efee__ for 
#define __obfs_1bb9__ (int 
#define __obfs_3a0772443a0739__ i 
#define __obfs_a9__ = 
#define __obfs_58ae__ 0; 
#define __obfs_4e4b5fbbbb602b__ i 
#define __obfs_8eefcfdf5990__ < 
#define __obfs_1728__ 5; 
#define __obfs_cbcb58ac2e496__ i++) 
#define __obfs_db85e2590b6__ { 
#define __obfs_99__ int 
#define __obfs_dd458505749b__ rowZombie[6] 
#define __obfs_8b16ebc0__ = 
#define __obfs_a86c450b76fb8c3__ {}, 
#define __obfs_c9892a989183de3__ RowZombie[6] 
#define __obfs_e6b4b2a74__ = 
#define __obfs_e5f6ad6ce374177__ {}; 
#define __obfs_f0e52b27a__ for 
#define __obfs_ffeabd2__ (int 
#define __obfs_a7aeed7471411__ j 
#define __obfs_fde9264cf376fff__ = 
#define __obfs_a8849b052__ 0; 
#define __obfs_258be18e31c8__ j 
#define __obfs_069d3bb__ < 
#define __obfs_c6e19e830859f2c__ 10; 
#define __obfs_46922a0880a8f1__ j++) 
#define __obfs_9ad6aaed5__ for 
#define __obfs_f5deaeeae1538__ (int 
#define __obfs_a9a1d5317a33ae8__ k 
#define __obfs_605ff764c617d3c__ = 
#define __obfs_766ebcd59__ 0; 
#define __obfs_dac__ k 
#define __obfs_30bb382__ < 
#define __obfs_08b2__ 10; 
#define __obfs_3493__ k++) 
#define __obfs_dbe272__ { 
#define __obfs_acc3e040464__ if 
#define __obfs_076a0c9__ (zombies[i][j][k] 
#define __obfs_04ecb1__ = 
#define __obfs_b2eeb7362ef8__ -1) 
#define __obfs_08___ break; 
#define __obfs_6aca9700__ else 
#define __obfs_3435c378bb76__ rowZombie[zombies[i][j][k]]++; 
#define __obfs_d49__ } 
#define __obfs_b2f627ff__ for 
#define __obfs_c3__ (int 
#define __obfs_d8__ j 
#define __obfs_9cf81d8026a__ = 
#define __obfs_c361bc7b2c033a8__ 0; 
#define __obfs_44__ j 
#define __obfs_dc82d6__ < 
#define __obfs_996__ 10; 
#define __obfs_d7a728a67d90__ j++) 
#define __obfs_00ac8ed3b4327b__ for 
#define __obfs_8ebda540cbcc4d73__ (int 
#define __obfs_f76a89f0c__ k 
#define __obfs_f29c2__ = 
#define __obfs_851ddf5058cf22__ 0; 
#define __obfs_58d4d1e7b__ k 
#define __obfs_7750ca3559e__ < 
#define __obfs_5d44__ 10; 
#define __obfs_eb6fd__ k++) 
#define __obfs_cdc0d6e__ { 
#define __obfs_b73dfe25b4b8__ if 
#define __obfs_85f__ (Zombies[i][j][k] 
#define __obfs_3871__ = 
#define __obfs_a733fa9b25f3368__ -1) 
#define __obfs_48ab2f9b4__ break; 
#define __obfs_23350907__ else 
#define __obfs_45645a27c__ RowZombie[Zombies[i][j][k]]++; 
#define __obfs_18__ ; 
#define __obfs_42e77b63637ab3__ } 
#define __obfs_051e4e127b92f5d__ for 
#define __obfs_9cc138f8dc04cb__ (int 
#define __obfs_b7bb35b9c6__ j 
#define __obfs_abd815286ba10__ = 
#define __obfs_26dd0__ 0; 
#define __obfs_6766aa2750__ j 
#define __obfs_6a10bb__ < 
#define __obfs_c5ab__ 6; 
#define __obfs_a53__ j++) 
#define __obfs_4c27cea8526a__ if 
#define __obfs_0f96613235__ (RowZombie[j] 
#define __obfs_4f__ > 
#define __obfs_67e1__ rowZombie[j]) 
#define __obfs_291597a100aadd__ zombieCostPerRow[i] 
#define __obfs_9b698__ += 
#define __obfs_8c7bbbba95c1025__ zombieCost[j]; 
#define __obfs_5e9f92a01c986ba__ } 
#define __obfs_0ff39b__ for 
#define __obfs_303ed4c69846ab36__ (int 
#define __obfs_443cb001c__ i 
#define __obfs_55b37c5c27__ = 
#define __obfs_884d24__ 0; 
#define __obfs_557__ i 
#define __obfs_30ef30b64204__ < 
#define __obfs_ea__ 7; 
#define __obfs_ab23__ i++) 
#define __obfs_3d2d8c__ { 
#define __obfs_26408ffa70__ if 
#define __obfs_b4288__ (z[i] 
#define __obfs_2f37d1__ < 
#define __obfs_0ff__ Z[i]) 
#define __obfs_68264bdb65b97__ { 
#define __obfs_3a066bda8c96b9__ } 
#define __obfs_be3159a__ else 
#define __obfs_8757150de__ if 
#define __obfs_22__ (z[i] 
#define __obfs_84117275b__ > 
#define __obfs_fae0b27c451c728__ Z[i]) 
#define __obfs_b5dc4e5d9__ { 
#define __obfs_192fc044e74d__ moon 
#define __obfs_5c__ -= 
#define __obfs_17c276c8e723eb46__ zombieCost[i]; 
#define __obfs_5dd9__ cdZombie[i] 
#define __obfs_2dea61eed4bcee__ = 
#define __obfs_9f396fe44e7c__ zombieCd[i]; 
#define __obfs_0d7de1aca9299__ flagZombie[i] 
#define __obfs_8fecb20817b3847__ = 
#define __obfs_dc6a70712a252123__ 0; 
#define __obfs_71a3cb155f8__ } 
#define __obfs_9fe8593a8__ } 
#define __obfs_ca9c267__ for 
#define __obfs_fccb3cdc__ (int 
#define __obfs_1595af64350__ i 
#define __obfs_08d98638c6fcd1__ = 
#define __obfs_246819284__ 0; 
#define __obfs_556f__ i 
#define __obfs_3328__ < 
#define __obfs_109a0__ 5; 
#define __obfs_7f5d04d189dfb6__ i++) 
#define __obfs_f79921bbae40a577__ { 
#define __obfs_07a96b1f61097ccb__ for 
#define __obfs_c06d06da__ (int 
#define __obfs_10a5ab2db37feedf__ j 
#define __obfs_e555ebe__ = 
#define __obfs_53e3a71__ 0; 
#define __obfs_5487__ j 
#define __obfs_e4bb4c5173c2ce1__ < 
#define __obfs_0cb929eae7a499__ 10; 
#define __obfs_8a0e1141fd__ j++) 
#define __obfs_99bcfcd754a9__ { 
#define __obfs_afd48__ int 
#define __obfs_e5841df2166dd__ k 
#define __obfs_b4a528955__ = 
#define __obfs_b1__ 0; 
#define __obfs_d6c651dd__ while 
#define __obfs_f64eac__ (Zombies[i][j][k] 
#define __obfs_4a4__ != 
#define __obfs_9c82c7143c102b71__ -1) 
#define __obfs_50__ { 
#define __obfs_ae0eb3eed39d2bc__ zombies[i][j][k] 
#define __obfs_1ecfb463472ec911__ = 
#define __obfs_e70611883d__ Zombies[i][j][k]; 
#define __obfs_60815949__ k++; 
#define __obfs_19bc916108fc__ } 
#define __obfs_07c5807d0d9__ } 
#define __obfs_d14__ } 
#define __obfs_8df707a948fac1b4__ vector<int> 
#define __obfs_e7__ have_erased; 
#define __obfs_788d9869__ for 
#define __obfs_50c3d__ (int 
#define __obfs_2afe4567e1bf__ i 
#define __obfs_5f2c22cb4a538__ = 
#define __obfs_aba3b6fd5d18__ 0; 
#define __obfs_c8ed21db4f__ i 
#define __obfs_084__ < 
#define __obfs_7f1171a__ vectorZombies.size(); 
#define __obfs_82f2__ i++) 
#define __obfs_0d31__ { 
#define __obfs_fb89705ae6d__ int 
#define __obfs_d4c2e4a3297__ have_erased_flag 
#define __obfs_5751ec3e9a__ = 
#define __obfs_d5cfead94f5350c__ 0; 
#define __obfs_59c33016884a6__ for 
#define __obfs_ba386__ (int 
#define __obfs_6c29793a140a8__ z 
#define __obfs_e995f98d5696__ = 
#define __obfs_6cd67d9b6f01__ 0; 
#define __obfs_6bc24fc1ab__ z 
#define __obfs_a5cdd4aa0048b1__ < 
#define __obfs_217eedd1ba8c__ have_erased.size(); 
#define __obfs_df263d__ z 
#define __obfs_edfbe1afcf__ += 
#define __obfs_2e65f__ 2) 
#define __obfs_e94550c93c__ { 
#define __obfs_5c572eca050594__ if 
#define __obfs_0537fb40a68c1__ (vectorZombies[i].coX 
#define __obfs_5f__ == 
#define __obfs_185e65bc405__ have_erased[z] 
#define __obfs_8d31__ && 
#define __obfs_e4__ vectorZombies[i].coY 
#define __obfs_b056eb1587586__ == 
#define __obfs_b137__ have_erased[z 
#define __obfs_912d2b1c7b28__ + 
#define __obfs_a1d33d__ 1]) 
#define __obfs_6f2268b__ { 
#define __obfs_872488f8__ have_erased_flag 
#define __obfs_ccb0989662__ = 
#define __obfs_2823f4797102__ 1; 
#define __obfs_470e7a__ break; 
#define __obfs_bf62768ca46b__ } 
#define __obfs_fa14d4fe__ } 
#define __obfs_2ca65f__ if 
#define __obfs_88ae6372cfdc5d__ (Plants[vectorZombies[i].coX][vectorZombies[i].coY] 
#define __obfs_06__ != 
#define __obfs_eefc9e10ebdc4a23__ SMALLNUT 
#define __obfs_58__ || 
#define __obfs_d840cc5d906c3__ have_erased_flag 
#define __obfs_959__ == 
#define __obfs_f220__ 1) 
#define __obfs_3a__ { 
#define __obfs_288cc0ff0228__ continue; 
#define __obfs_4e__ } 
#define __obfs_b7ee6f5f9__ else 
#define __obfs_e57c6b956a65__ { 
#define __obfs_86b12__ int 
#define __obfs_4e0928de__ num 
#define __obfs_c0f16__ = 
#define __obfs_8c6744c__ vectorZombies[i].num; 
#define __obfs_f1c1592__ int 
#define __obfs_e07413354__ original_num_of_this_kind 
#define __obfs_67__ = 
#define __obfs_a8e864d04c9__ 0, 
#define __obfs_7143d7fb__ now_num_of_this_kind 
#define __obfs_72da7fd6d1302c0a__ = 
#define __obfs_6e0721b2c6__ 0; 
#define __obfs_fc8001f8__ int 
#define __obfs_4b04a686b0ad1__ k 
#define __obfs_61b4a64b__ = 
#define __obfs_3621f1454cacf__ 0; 
#define __obfs_c15da1f2b__ while 
#define __obfs_68053af2__ (zombies[vectorZombies[i].coX][vectorZombies[i].coY][k] 
#define __obfs_2dace78f80bc92__ != 
#define __obfs_df7f28ac89ca__ -1) 
#define __obfs_96e__ { 
#define __obfs_da8ce__ if 
#define __obfs_8248__ (zombies[vectorZombies[i].coX][vectorZombies[i].coY][k] 
#define __obfs_7c590f01__ == 
#define __obfs_35cf__ num) 
#define __obfs_beb22fb694d513ed__ { 
#define __obfs_9e3cfc48__ original_num_of_this_kind++; 
#define __obfs_28267__ } 
#define __obfs_7a53928fa4dd__ k++; 
#define __obfs_1905a__ } 
#define __obfs_1141938ba2c2__ k 
#define __obfs_1aa__ = 
#define __obfs_dc5689792e08eb2e__ 0; 
#define __obfs_846c260d715e5b__ while 
#define __obfs_d58072be2820e86__ (Zombies[vectorZombies[i].coX][vectorZombies[i].coY][k] 
#define __obfs_6e7b33fdea__ != 
#define __obfs_a8ecbabae151aba__ -1) 
#define __obfs_32b30a250abd6331__ { 
#define __obfs_b6edc1cd1f__ if 
#define __obfs_67___ (Zombies[vectorZombies[i].coX][vectorZombies[i].coY][k] 
#define __obfs_81e74d67858__ == 
#define __obfs_e0cf1f47118__ num) 
#define __obfs_96b__ { 
#define __obfs_71ad16__ now_num_of_this_kind++; 
#define __obfs_43fa7f58b7__ } 
#define __obfs_31839b036f638__ k++; 
#define __obfs_f0adc__ } 
#define __obfs_3b5d__ if 
#define __obfs_e2a2dcc36a08a345__ (original_num_of_this_kind 
#define __obfs_4558dbb6f6f8b__ - 
#define __obfs_afda3322__ now_num_of_this_kind 
#define __obfs_632cee946__ > 
#define __obfs_677e09724f0e2d__ 0) 
#define __obfs_d554__ { 
#define __obfs_795c7a7a5ec__ vector<int> 
#define __obfs_fa3a3c407f8__ serialNum; 
#define __obfs_c2626__ for 
#define __obfs_ce78d1__ (int 
#define __obfs_8e82ab__ j 
#define __obfs_e0ec4__ = 
#define __obfs_7250eb93b3c18cc__ 0; 
#define __obfs_013a006f03dbc53__ j 
#define __obfs_301__ < 
#define __obfs_4d5b__ vectorZombies.size(); 
#define __obfs_ab88b15733__ j++) 
#define __obfs_b0b18__ { 
#define __obfs_f90__ if 
#define __obfs_8f7d__ (vectorZombies[j].num 
#define __obfs_fa83a11a1__ == 
#define __obfs_02a__ num 
#define __obfs_fc3cf452d3da8402__ && 
#define __obfs_3d8e28caf90131__ vectorZombies[i].coY 
#define __obfs_e97ee205__ == 
#define __obfs_b86e8d03f__ vectorZombies[j].coY 
#define __obfs_84__ && 
#define __obfs_f4552__ vectorZombies[i].coX 
#define __obfs_362e__ == 
#define __obfs_fe__ vectorZombies[j].coX) 
#define __obfs_1efa39b__ { 
#define __obfs_92fb0c6d175826__ serialNum.push_back(j); 
#define __obfs_22ac3c5a5bf__ } 
#define __obfs_aff__ } 
#define __obfs_f7e9050c9__ if 
#define __obfs_addfa9b7e234__ (now_num_of_this_kind 
#define __obfs_8c235f89a8143a__ == 
#define __obfs_847cc55b7032__ 0) 
#define __obfs_a67f09__ { 
#define __obfs_2a084e55c87b1e__ for 
#define __obfs_fc49306d97602__ (int 
#define __obfs_f9a__ i 
#define __obfs_5ec91aac30ea__ = 
#define __obfs_19b650660b25__ serialNum.size() 
#define __obfs_1fc214004c__ - 
#define __obfs_3b3dbaf685__ 1; 
#define __obfs_ca__ i 
#define __obfs_ede7e2b6d13a41dd__ >= 
#define __obfs_dd45045f8c68__ 0; 
#define __obfs_49c9adb18e4__ i--) 
#define __obfs_22fb0cee7e1f3bd__ { 
#define __obfs_aeb3135b436aa55__ vectorZombies.erase(serialNum[i] 
#define __obfs_43feaeeecd7b2fe__ + 
#define __obfs_98__ vectorZombies.begin()); 
#define __obfs_51__ } 
#define __obfs_4b0a59ddf11c58__ } 
#define __obfs_67d16__ if 
#define __obfs_352407221afb__ (original_num_of_this_kind 
#define __obfs_dd8eb9f23fbd36__ - 
#define __obfs_d516b136__ now_num_of_this_kind 
#define __obfs_1f5089__ == 
#define __obfs_7504adad8bb96320__ 1) 
#define __obfs_6c3cf77__ { 
#define __obfs_210f760a89db30aa__ int 
#define __obfs_17__ small_hp 
#define __obfs_0efe32849d230d__ = 
#define __obfs_704a__ 5000, 
#define __obfs_7ce3284b743aefde__ small_hp_num 
#define __obfs_0a113__ = 
#define __obfs_07871915a81071__ 0; 
#define __obfs_024__ for 
#define __obfs_cf__ (int 
#define __obfs_c2a__ k 
#define __obfs_d56b9fc4b0f1be8__ = 
#define __obfs_4b02507935__ 0; 
#define __obfs_20__ k 
#define __obfs_061412e4__ < 
#define __obfs_5705e1164a8394a__ serialNum.size(); 
#define __obfs_a64c9__ k++) 
#define __obfs_0188__ { 
#define __obfs_acf4b89d3__ if 
#define __obfs_892c91e0a653__ (small_hp 
#define __obfs_b6a1085a27ab7__ > 
#define __obfs_aa169__ vectorZombies[serialNum[k]].hp) 
#define __obfs_f47d0a__ { 
#define __obfs_f57__ small_hp 
#define __obfs_c8fbbc86__ = 
#define __obfs_621461af90cadfda__ vectorZombies[serialNum[k]].hp; 
#define __obfs_8b6dd7db9af4__ small_hp_num 
#define __obfs_a4300b002bcfb71__ = 
#define __obfs_e205ee__ k; 
#define __obfs_b56a__ } 
#define __obfs_2a9d__ } 
#define __obfs_8b5040a8__ vectorZombies.erase(small_hp_num 
#define __obfs_7634ea65a4e__ + 
#define __obfs_248__ vectorZombies.begin()); 
#define __obfs_23ce__ } 
#define __obfs_da0d1111d2dc5__ have_erased.push_back(vectorZombies[i].coX); 
#define __obfs_1e056d2b__ have_erased.push_back(vectorZombies[i].coY); 
#define __obfs_3e89ebdb49f7__ } 
#define __obfs_6d0__ } 
#define __obfs_430c3626b879b__ } 
#define __obfs_ccc0aa1__ for 
#define __obfs_c4015b7f368e6b__ (int 
#define __obfs_bea5__ i 
#define __obfs_7fa732b517cb__ = 
#define __obfs_cbb6a__ 0; 
#define __obfs_1f4477b__ i 
#define __obfs_d045c59a90__ < 
#define __obfs_0d0871f08__ vectorZombies.size(); 
#define __obfs_1cc363__ i++) 
#define __obfs_9f53d83__ { 
#define __obfs_d2ed45a52__ int 
#define __obfs_043c3d7e489c6__ num 
#define __obfs_4daa3db355ef2b0__ = 
#define __obfs_e820a45f1dfc7b95__ vectorZombies[i].num; 
#define __obfs_90794e3b050__ int 
#define __obfs_b7892fb3c2f00__ k 
#define __obfs_74bba22728b6185__ = 
#define __obfs_3df1d4b96d8976__ 0; 
#define __obfs_8d6dc35e__ int 
#define __obfs_92262bf__ flag_self 
#define __obfs_b55ec28c5__ = 
#define __obfs_2f88__ 0; 
#define __obfs_6422__ int 
#define __obfs_4b6538a44a1df__ flag_near 
#define __obfs_c8c41c4a18675a__ = 
#define __obfs_c4b31ce7d95c7__ 0; 
#define __obfs_58e4d44e550d0f7e__ while 
#define __obfs_3cef9__ (Zombies[vectorZombies[i].coX][vectorZombies[i].coY][k] 
#define __obfs_a3d68b461bd9d35__ != 
#define __obfs_1c1d4df596d__ -1) 
#define __obfs_e6cb2a3c14__ { 
#define __obfs_9232fe81225__ if 
#define __obfs_6395ebd0f4b47__ (num 
#define __obfs_ef4e3b__ == 
#define __obfs_168__ Zombies[vectorZombies[i].coX][vectorZombies[i].coY][k]) 
#define __obfs_2ba5__ { 
#define __obfs_d240e3d__ break; 
#define __obfs_0f__ } 
#define __obfs_437d7d1d97917__ else 
#define __obfs_d707329bece455a__ { 
#define __obfs_5c936263f__ flag_self 
#define __obfs_1c__ = 
#define __obfs_8065d07da4a7762__ 1; 
#define __obfs_eeb69a3cb9__ } 
#define __obfs_4e0c__ } 
#define __obfs_6cfe0e6127fa__ k 
#define __obfs_8f468c873__ = 
#define __obfs_e744f9__ 0; 
#define __obfs_89fcd07f20b6785b__ while 
#define __obfs_6602294be91__ (Zombies[vectorZombies[i].coX][vectorZombies[i].coY 
#define __obfs_c22abfa379f3__ - 
#define __obfs_ca7__ 1][k] 
#define __obfs_4311359ed4969e8__ != 
#define __obfs_92977ae__ -1) 
#define __obfs_9c01802ddb981e6b__ { 
#define __obfs_cc__ if 
#define __obfs_2ab56412b1163ee__ (num 
#define __obfs_c32d9bf27a3da__ == 
#define __obfs_d79aac075930c83__ Zombies[vectorZombies[i].coX][vectorZombies[i].coY][k]) 
#define __obfs_287e03db1d99e0__ { 
#define __obfs_fec__ vectorZombies[i].coY--; 
#define __obfs_6aa__ } 
#define __obfs_d93ed5b6db83b__ else 
#define __obfs_54a367d6291__ { 
#define __obfs_fe___ flag_near 
#define __obfs_df6d233__ = 
#define __obfs_9908279eb__ 1; 
#define __obfs_a1140__ } 
#define __obfs_4fac9ba115140a__ } 
#define __obfs_692f93b__ if 
#define __obfs_860320be12a1c050__ (flag_self 
#define __obfs_7b13b2203029e__ == 
#define __obfs_934815ad542__ 1 
#define __obfs_2bcab9d9__ && 
#define __obfs_0b8aff__ flag_near 
#define __obfs_ec5aa0b__ == 
#define __obfs_9ab0d8843__ 1) 
#define __obfs_b70683__ { 
#define __obfs_a9b7ba70783b6__ vectorZombies.erase(vectorZombies.begin() 
#define __obfs_b8c37e33defde51c__ + 
#define __obfs_fba__ i); 
#define __obfs_aa68c75c4__ i--; 
#define __obfs_fed3__ } 
#define __obfs_2387337ba1e__ } 
#define __obfs_9246444d9__ for 
#define __obfs_d7322ed717dedf__ (int 
#define __obfs_1587965fb4d__ i 
#define __obfs_31b__ = 
#define __obfs_1e48c4420b70__ 0; 
#define __obfs_7f975__ i 
#define __obfs_f33ba15eff__ < 
#define __obfs_6b__ 7; 
#define __obfs_766d85__ i++) 
#define __obfs_298923c8190045__ { 
#define __obfs_08fe2621d8e716b0__ if 
#define __obfs_5d6__ (cdPlant[i] 
#define __obfs_ef__ > 
#define __obfs_03e0704__ 0) 
#define __obfs_65cc2c8205a05d7__ cdPlant[i]--; 
#define __obfs_0768281a05da9__ if 
#define __obfs_93d65641ff3f1__ (cdPlant[i] 
#define __obfs_ce5140df15d04__ == 
#define __obfs_021bb__ 0) 
#define __obfs_82b8__ flagPlant[i] 
#define __obfs_24___ = 
#define __obfs_88__ 1; 
#define __obfs_3806734b256c27e4__ } 
#define __obfs_84d__ for 
#define __obfs_e515df0d20__ (int 
#define __obfs_afdec7005cc9f1__ i 
#define __obfs_995e1fda4__ = 
#define __obfs_e1___ 0; 
#define __obfs_bdb106a0560c4e__ i 
#define __obfs_a34bacf__ < 
#define __obfs_83fa5a432ae55__ 6; 
#define __obfs_eddb90__ i++) 
#define __obfs_6d70cb65d15211__ { 
#define __obfs_27ed0fb950b856b0__ if 
#define __obfs_537d9b6__ (cdZombie[i] 
#define __obfs_d736bb10d83a904a__ > 
#define __obfs_9a__ 0) 
#define __obfs_b9141aff1412dc76__ cdZombie[i]--; 
#define __obfs_1019c8091693__ if 
#define __obfs_a0e2__ (cdZombie[i] 
#define __obfs_1579779b98__ == 
#define __obfs_20b5e1__ 0) 
#define __obfs_7cce53cf90577__ flagZombie[i] 
#define __obfs_58c54802a9fb9526__ = 
#define __obfs_50___ 1; 
#define __obfs_45___ } 
#define __obfs_f4dd765c1__ for 
#define __obfs_7fe__ (int 
#define __obfs_db576a7d24535__ i 
#define __obfs_53c__ = 
#define __obfs_4ca82782c5372a5__ 0; 
#define __obfs_d8700cbd3__ i 
#define __obfs_b4d168b48__ < 
#define __obfs_4a08142__ sunFlowers.size(); 
#define __obfs_29__ i++) 
#define __obfs_a89cf525__ { 
#define __obfs_cd89fef__ if 
#define __obfs_6c340f__ (sunFlowers[i].cd 
#define __obfs_2290a7__ > 
#define __obfs_a2137a2ae8e39__ 0) 
#define __obfs_43dd49b4fdb9b__ sunFlowers[i].cd--; 
#define __obfs_31857b449c40__ if 
#define __obfs_53adaf494__ (sunFlowers[i].cd 
#define __obfs_fc2c7c4__ == 
#define __obfs_dc58e3a306451c9d__ 0) 
#define __obfs_1b0114c51cc532e__ { 
#define __obfs_a1519de5b5__ sun 
#define __obfs_390__ += 
#define __obfs_708f3cf__ 25; 
#define __obfs_46072631582f__ sunFlowers[i].cd 
#define __obfs_8a1e808b5__ = 
#define __obfs_062ddb6c72__ 24; 
#define __obfs_522a9ae__ } 
#define __obfs_43baa676__ } 
#define __obfs_731c83db8d2ff01__ } 
#define __obfs_36a16a25053__ Game() 
#define __obfs_818f4654ed39a__ { 
#define __obfs_e5e63da79fcd2b__ time 
#define __obfs_9f36407ead06__ = 
#define __obfs_4f16c818875d__ 0; 
#define __obfs_d91d1b4d82419de__ sun 
#define __obfs_a263__ = 
#define __obfs_b1___ 400, 
#define __obfs_03f5446139179452__ moon 
#define __obfs_8b__ = 
#define __obfs_754dda4b__ 300; 
#define __obfs_6a2fee__ for 
#define __obfs_68b1__ (int 
#define __obfs_41bfd20a38bb1b0__ i 
#define __obfs_d6723e7__ = 
#define __obfs_4e___ 0; 
#define __obfs_db2b4__ i 
#define __obfs_a5e0ff__ < 
#define __obfs_a0160709701140__ 5; 
#define __obfs_1e6__ i++) 
#define __obfs_c6bff625bdb0393__ for 
#define __obfs_c667__ (int 
#define __obfs_aace49c7d80767cf__ j 
#define __obfs_4da04049a__ = 
#define __obfs_af21d0c__ 0; 
#define __obfs_c9__ j 
#define __obfs_e58cc5ca942__ < 
#define __obfs_b9d487a30398__ 10; 
#define __obfs_8f1d43620b__ j++) 
#define __obfs_2cbca44843__ plants[i][j] 
#define __obfs_b59__ = 
#define __obfs_20d135f0f28185b8__ 0, 
#define __obfs_9c3b__ flagShovel[i][j] 
#define __obfs_d6ef5f7fa914c19__ = 
#define __obfs_e19__ 0; 
#define __obfs_dd77279__ for 
#define __obfs_0eec27c419d0fe24__ (int 
#define __obfs_c60d060__ i 
#define __obfs_8597a6c__ = 
#define __obfs_c6036a69be21cb66__ 0; 
#define __obfs_3a15c7d0bbe__ i 
#define __obfs_3b712de__ < 
#define __obfs_2cfd4560539f8__ 5; 
#define __obfs_c7635bfd99__ i++) 
#define __obfs_c21__ for 
#define __obfs_ffeed84c7c__ (int 
#define __obfs_678a1491514b7__ j 
#define __obfs_3fe78a8acf5fda__ = 
#define __obfs_69a5b5995110b36a__ 0; 
#define __obfs_4a213d37242bdca__ j 
#define __obfs_fe709c654e__ < 
#define __obfs_571e0f7e2d992e__ 10; 
#define __obfs_fd0__ j++) 
#define __obfs_7c9__ for 
#define __obfs_fd2c5e468__ (int 
#define __obfs_47a__ k 
#define __obfs_801c14f07f__ = 
#define __obfs_c3e0c62ee91db8d__ 0; 
#define __obfs_1842603__ k 
#define __obfs_8248a99e81e75__ < 
#define __obfs_f7f580e11d00a__ 10; 
#define __obfs_8ce6790c__ k++) 
#define __obfs_208e4__ zombies[i][j][k] 
#define __obfs_4588e6__ = 
#define __obfs_feab05aa91085b7__ 0; 
#define __obfs_8a__ for 
#define __obfs_a1d50185e7426cb__ (int 
#define __obfs_df0a__ i 
#define __obfs_09c6c3783b__ = 
#define __obfs_2b3__ 0; 
#define __obfs_f197002b9__ i 
#define __obfs_45f31d16b1058__ < 
#define __obfs_55b__ 5; 
#define __obfs_e8b1cbd05f6e6a35__ i++) 
#define __obfs_285f89b802bcb2__ dps[i] 
#define __obfs_e22312179bf43e__ = 
#define __obfs_a8240cb82__ 0, 
#define __obfs_0c048b3a434e49__ zombieCostPerRow[i] 
#define __obfs_16e6a3__ = 
#define __obfs_884d79963bd__ 0; 
#define __obfs_38ca895__ for 
#define __obfs_abea47ba24__ (int 
#define __obfs_6e7d2da6d3953__ i 
#define __obfs_00e26af6a__ = 
#define __obfs_a3fb4f__ 0; 
#define __obfs_0f2c9a93ee__ i 
#define __obfs_9da__ < 
#define __obfs_2f29b6e__ 7; 
#define __obfs_1e1d184167ca__ i++) 
#define __obfs_3eb71f62__ cdPlant[i] 
#define __obfs_a113c1ec__ = 
#define __obfs_36a1694bce9815b__ 0, 
#define __obfs_0a0a0__ flagPlant[i] 
#define __obfs_3473decccb__ = 
#define __obfs_1896a3bf730516__ 1; 
#define __obfs_a7d8__ for 
#define __obfs_83f97f48252__ (int 
#define __obfs_7d__ i 
#define __obfs_dabd8d2ce74e__ = 
#define __obfs_6eb6e75fddec__ 0; 
#define __obfs_2ac24__ i 
#define __obfs_f473306__ < 
#define __obfs_0e095e054ee9477__ 6; 
#define __obfs_97af4fb322__ i++) 
#define __obfs_568__ cdZombie[i] 
#define __obfs_2b6d65b9__ = 
#define __obfs_4f28480__ 0, 
#define __obfs_c44e503833b6__ flagZombie[i] 
#define __obfs_82c255__ = 
#define __obfs_160c88652d47d0be__ 1; 
#define __obfs_b20bb95ab626d__ } 
#define __obfs_52292e0c763__ Game 
#define __obfs_9a3d458322__ tranState(Actionlist 
#define __obfs_a42a596__ q, 
#define __obfs_0188e8b8b014829e__ IPlayer 
#define __obfs_9adeb82fffb54__ *player); 
#define __obfs_ae5e3ce__ }; 
#define __obfs_c54e7837e0c__ Game 
#define __obfs_4d2e7bd33c475__ Game::tranState(Actionlist 
#define __obfs_fe2d010__ q, 
#define __obfs_7501e5d4da87__ IPlayer 
#define __obfs_14770__ *player) 
#define __obfs_491442df__ { 
#define __obfs_fb2fcd534b0__ Game 
#define __obfs_b571ecea1__ newGame; 
#define __obfs_144a3f71a03ab7__ { 
#define __obfs_4e4e53aa080247b__ newGame.time 
#define __obfs_a58149d355f02__ = 
#define __obfs_7e7e69ea3384__ this->time, 
#define __obfs_f7cade80b7cc92b__ newGame.sun 
#define __obfs_285ab9448d2__ = 
#define __obfs_a016__ this->sun, 
#define __obfs_33ceb07bf4ee__ newGame.moon 
#define __obfs_c8__ = 
#define __obfs_a4d2__ this->moon; 
#define __obfs_3948ead6__ for 
#define __obfs_6a61d423d02a1__ (int 
#define __obfs_3f67fd9716__ i 
#define __obfs_27155__ = 
#define __obfs_b24d516bb65a5a__ 0; 
#define __obfs_1d72310edc006dad__ i 
#define __obfs_3a029f04d76d3__ < 
#define __obfs_43cca4__ 5; 
#define __obfs_68___ i++) 
#define __obfs_25df__ for 
#define __obfs_3210ddbeaa16948a__ (int 
#define __obfs_c4851__ j 
#define __obfs_eb86d510361fc23b__ = 
#define __obfs_310c__ 0; 
#define __obfs_41__ j 
#define __obfs_6c1__ < 
#define __obfs_e53a0a297__ 10; 
#define __obfs_e034fb6b66a__ j++) 
#define __obfs_81dc9bdb52d0__ newGame.plants[i][j] 
#define __obfs_9996535e07258a__ = 
#define __obfs_7bcc__ this->plants[i][j], 
#define __obfs_a9eb8__ flagShovel[i][j] 
#define __obfs_d3890__ = 
#define __obfs_b3ba8f1bee__ this->flagShovel[i][j]; 
#define __obfs_a9078e8653368c9__ for 
#define __obfs_1c65cef3dfd1__ (int 
#define __obfs_2de5d166__ i 
#define __obfs_e1d5be1c7__ = 
#define __obfs_2c89109d421__ 0; 
#define __obfs_5eac43ac__ i 
#define __obfs_905056c1ac1dad1__ < 
#define __obfs_e6d8545daa42d5__ 5; 
#define __obfs_39e4973ba3321__ i++) 
#define __obfs_2ba8698b7943958__ for 
#define __obfs_81e5f8__ (int 
#define __obfs_838e__ j 
#define __obfs_a284d__ = 
#define __obfs_b495__ 0; 
#define __obfs_884ce4bb65d__ j 
#define __obfs_3bf55bbad370__ < 
#define __obfs_e3251075__ 10; 
#define __obfs_cd__ j++) 
#define __obfs_26588e932__ for 
#define __obfs_68a__ (int 
#define __obfs_f4__ k 
#define __obfs_17326d10d__ = 
#define __obfs_dc4c4__ 0; 
#define __obfs_7eb__ k 
#define __obfs_6c8dba7d0df1c4a7__ < 
#define __obfs_0c__ 10; 
#define __obfs_8e2cfdc275761__ k++) 
#define __obfs_b51a15f382ac914__ newGame.zombies[i][j][k] 
#define __obfs_19___ = 
#define __obfs_e00406144c1__ this->zombies[i][j][k]; 
#define __obfs_c850371f__ for 
#define __obfs_c1e39d912d21c9__ (int 
#define __obfs_781__ i 
#define __obfs_f91e24dfe__ = 
#define __obfs_e702e5__ 0; 
#define __obfs_bb04a__ i 
#define __obfs_fb60d4__ < 
#define __obfs_d759175de8ea5b1__ 7; 
#define __obfs_ab1a4d0dd4d48a2__ i++) 
#define __obfs_99566__ newGame.cdPlant[i] 
#define __obfs_da11e8cd181__ = 
#define __obfs_d94e__ this->cdPlant[i], 
#define __obfs_1ce__ newGame.flagPlant[i] 
#define __obfs_018b59ce__ = 
#define __obfs_242c__ this->flagPlant[i]; 
#define __obfs_944__ for 
#define __obfs_c0a271__ (int 
#define __obfs_40790__ i 
#define __obfs_0e9fa1f3e9__ = 
#define __obfs_0829424ffa0d3__ 0; 
#define __obfs_70222949cc0__ i 
#define __obfs_71f6278d140af__ < 
#define __obfs_459a4ddcb5__ 6; 
#define __obfs_7c82fab8c8__ i++) 
#define __obfs_84438b7aae__ newGame.cdZombie[i] 
#define __obfs_dc87c13749315__ = 
#define __obfs_2812e5cf6d8f21d6__ this->cdZombie[i], 
#define __obfs_2866__ newGame.flagZombie[i] 
#define __obfs_a51fb975227d6__ = 
#define __obfs_a0833c8a1__ this->flagZombie[i]; 
#define __obfs_6f__ for 
#define __obfs_2df__ (int 
#define __obfs_996009f2374__ i 
#define __obfs_d282ef263719ab8__ = 
#define __obfs_5ca__ 0; 
#define __obfs_fd5c90__ i 
#define __obfs_7940ab4746__ < 
#define __obfs_f9__ 5; 
#define __obfs_a0872cc__ i++) 
#define __obfs_447__ newGame.dps[i] 
#define __obfs_535ab76633d94__ = 
#define __obfs_7bb0607__ this->dps[i], 
#define __obfs_f29b38f160f87ae8__ newGame.zombieCostPerRow[i] 
#define __obfs_f0969691__ = 
#define __obfs_50905d7b__ this->zombieCostPerRow[i]; 
#define __obfs_dfd7468ac613286__ } 
#define __obfs_f3f1b7fc5a8779__ for 
#define __obfs_93fb9__ (int 
#define __obfs_76cf99d3614e23ea__ i 
#define __obfs_1ee3__ = 
#define __obfs_2a50e9c__ 0; 
#define __obfs_f9be311e__ i 
#define __obfs_dc960c46c38b__ < 
#define __obfs_4671aeaf49__ 5; 
#define __obfs_bb7946e7d8__ i++) 
#define __obfs_3546ab4__ for 
#define __obfs_c70daf24__ (int 
#define __obfs_17___ j 
#define __obfs_4c22bd444899d3__ = 
#define __obfs_01e95__ 0; 
#define __obfs_fe515__ j 
#define __obfs_e077e1a544__ < 
#define __obfs_28e2__ 10; 
#define __obfs_ff49cc40a__ j++) 
#define __obfs_8edd72158ccd2a__ { 
#define __obfs_9cb__ if 
#define __obfs_3d77__ (q.plantPlace[i][j] 
#define __obfs_e4___ > 
#define __obfs_05311655a1__ 0) 
#define __obfs_d10ec7c16cbe__ { 
#define __obfs_4f87658ef0de1__ int 
#define __obfs_33e__ num 
#define __obfs_5e1b18c__ = 
#define __obfs_674bfc5f6__ q.plantPlace[i][j]; 
#define __obfs_a50abba8132a7719__ newGame.sun 
#define __obfs_86109d400f0ed2__ -= 
#define __obfs_82965d4e__ plantCost[num]; 
#define __obfs_0e5566__ newGame.cdPlant[num] 
#define __obfs_c73dfe6c63__ = 
#define __obfs_bcc0d4002__ plantCd[num]; 
#define __obfs_861dc9b__ newGame.flagPlant[num] 
#define __obfs_3e313b__ = 
#define __obfs_8b0dc65f996__ 0; 
#define __obfs_ee8374ec4e__ newGame.dps[i] 
#define __obfs_af473271166105__ += 
#define __obfs_b8c27b7a1c450ff__ plantDps[num]; 
#define __obfs_980ecd059122c__ newGame.plants[i][j] 
#define __obfs_c2__ = 
#define __obfs_83adc9225e4d__ num; 
#define __obfs_8d3369c4c086__ } 
#define __obfs_fb__ if 
#define __obfs_cf9a242b7__ (q.zombiePlace[i] 
#define __obfs_a9be4c2a4041__ > 
#define __obfs_9683cc__ 0) 
#define __obfs_effc299a1a__ { 
#define __obfs_cf1f78fe923afe05__ int 
#define __obfs_6a5__ num 
#define __obfs_a2__ = 
#define __obfs_6c1da886822c__ q.zombiePlace[i]; 
#define __obfs_0e3a37aa8__ newGame.moon 
#define __obfs_d1ee59e20ad0__ -= 
#define __obfs_81ca0262c82__ zombieCost[num]; 
#define __obfs_f3bd5ad57c__ newGame.cdZombie[num] 
#define __obfs_e56b06c__ = 
#define __obfs_792c7b5__ zombieCd[num]; 
#define __obfs_70__ newGame.flagZombie[num] 
#define __obfs_79a49b__ = 
#define __obfs_f523__ 0; 
#define __obfs_8d9a0adb7c204239__ } 
#define __obfs_bad5f33__ } 
#define __obfs_ea8fcd92d59__ newGame.maintain(player); 
#define __obfs_d82118376df34__ return 
#define __obfs_4e0d67e54ad__ newGame; 
#define __obfs_cd0dce8fca267b__ } 
#define __obfs_5ca3e9b1__ class 
#define __obfs_86e8f7ab32cfd__ Zombies_num 
#define __obfs_363763__ { 
#define __obfs_4f___ public: 
#define __obfs_0c0a7__ int 
#define __obfs_2bd7f__ normal; 
#define __obfs_359f38463d__ int 
#define __obfs_7f53__ bucket; 
#define __obfs_c0826819636026__ int 
#define __obfs_ad__ polevault; 
#define __obfs_f016e59c7ad8b1d7__ int 
#define __obfs_14d9e8007c9__ sled; 
#define __obfs_09662890__ int 
#define __obfs_215__ gargantuar; 
#define __obfs_d97313__ int 
#define __obfs_602d1305678a__ total_num; 
#define __obfs_f0dd4a99fba6075a__ Zombies_num() 
#define __obfs_9701a1c165dd94__ { 
#define __obfs_28fc2782ea7e__ this->normal 
#define __obfs_4ed__ = 
#define __obfs_186a157b2992__ this->bucket 
#define __obfs_3de2334a314__ = 
#define __obfs_b7087c1f4__ this->polevault 
#define __obfs_46771d1f432b4__ = 
#define __obfs_6d9c__ this->sled 
#define __obfs_7b5b23f4aa__ = 
#define __obfs_512c5ca__ this->gargantuar 
#define __obfs_54072f485cdb789__ = 
#define __obfs_0e4e946668cf2__ this->total_num 
#define __obfs_59f51fd693741__ = 
#define __obfs_7a674153c__ 0; 
#define __obfs_a60937eba__ } 
#define __obfs_23ad3e31__ void 
#define __obfs_9a17__ compute_num(int 
#define __obfs_309__ ***zombies, 
#define __obfs_30c8e1ca87252__ int 
#define __obfs_90db9da__ rows, 
#define __obfs_9aa42b31882e__ int 
#define __obfs_0ed9422357395__ columns) 
#define __obfs_856__ { 
#define __obfs_489d0396e6826eb__ int 
#define __obfs_a424ed4__ num 
#define __obfs_299f__ = 
#define __obfs_970af__ 0; 
#define __obfs_0663a4__ for 
#define __obfs_56352739f5964354__ (int 
#define __obfs_411ae1bf081d167__ i 
#define __obfs_e11943a6031__ = 
#define __obfs_56468d5607a5aa__ 0; 
#define __obfs_b069b3__ i 
#define __obfs_78__ < 
#define __obfs_1f3202d820180a__ rows; 
#define __obfs_eaa32c96f620053c__ i++) 
#define __obfs_a8f8f6026__ { 
#define __obfs_db6ebd__ for 
#define __obfs_540ae6b0f6ac6e15__ (int 
#define __obfs_f4a331b__ j 
#define __obfs_b197ffdef2d__ = 
#define __obfs_f69e__ 0; 
#define __obfs_8fb5f8be2aa9d6c6__ j 
#define __obfs_afe434653a898da__ < 
#define __obfs_b265ce60fe4c53__ columns; 
#define __obfs_8fb21ee7a22__ j++) 
#define __obfs_c930eecd01935fee__ { 
#define __obfs_e94f63f57__ int 
#define __obfs_2dffbc474aa1__ k 
#define __obfs_c5cc17e395d30__ = 
#define __obfs_80a8155e__ 0; 
#define __obfs_6786__ while 
#define __obfs_53__ (zombies[i][j][k] 
#define __obfs_3bbfdde8842a__ != 
#define __obfs_0a1bf96b7__ -1) 
#define __obfs_5e76__ { 
#define __obfs_01d8b__ switch 
#define __obfs_4d__ (zombies[i][j][k]) 
#define __obfs_1abb1e1ea5__ { 
#define __obfs_07042ac7__ case 
#define __obfs_95151403b0__ NORMAL: 
#define __obfs_ad71c__ this->normal++; 
#define __obfs_fe70c3__ break; 
#define __obfs_c913303f__ case 
#define __obfs_372d3f30__ BUCKET: 
#define __obfs_6d9__ this->bucket++; 
#define __obfs_0245952ecff55018__ break; 
#define __obfs_cec6f62cfb44__ case 
#define __obfs_991de292__ POLEVAULT: 
#define __obfs_42f__ this->polevault++; 
#define __obfs_8b0d2__ break; 
#define __obfs_da__ case 
#define __obfs_ac796__ SLED: 
#define __obfs_7d6044e95a1__ this->sled++; 
#define __obfs_571d3a9420__ break; 
#define __obfs_97275a23ca__ case 
#define __obfs_78b__ GARGANTUAR: 
#define __obfs_83cdcec08fbf903__ this->gargantuar++; 
#define __obfs_dc09c97f__ break; 
#define __obfs_e816c635cad__ } 
#define __obfs_4e8412ad4__ num++; 
#define __obfs_ab5__ k++; 
#define __obfs_bff__ } 
#define __obfs_729c68884bd__ } 
#define __obfs_7fb__ } 
#define __obfs_86df7dcfd8__ } 
#define __obfs_6d3a1e06d6a0634__ }; 
#define __obfs_8a146f1a3__ class 
#define __obfs_1baff70e2669e8__ Plants_num 
#define __obfs_f187a__ { 
#define __obfs_226d1f15ecd35f7__ public: 
#define __obfs_e655c7716a4b3e__ int 
#define __obfs_1714726c817__ sunflower; 
#define __obfs_fcdf25d6e191893__ int 
#define __obfs_fa1e__ winterpeashooter; 
#define __obfs_1415db70fe9__ int 
#define __obfs_55c5__ peashooter; 
#define __obfs_ced__ int 
#define __obfs_6490791e7__ smallnut; 
#define __obfs_cf___ int 
#define __obfs_5cbdfd__ pepper; 
#define __obfs_77f95__ int 
#define __obfs_0c8ce55163055c4d__ squash; 
#define __obfs_49b8b4f95__ Plants_num() 
#define __obfs_0c9e__ { 
#define __obfs_b5488aeff__ this->sunflower 
#define __obfs_4dcf43543__ = 
#define __obfs_ebd6d2f5d60f__ this->winterpeashooter 
#define __obfs_1cd388239452087__ = 
#define __obfs_41a60377ba920919__ this->peashooter 
#define __obfs_ebb7104545__ = 
#define __obfs_0f3d014ee__ this->smallnut 
#define __obfs_2b3bf3eee__ = 
#define __obfs_83f2550__ this->pepper 
#define __obfs_bc___ = 
#define __obfs_490__ this->squash 
#define __obfs_81c8__ = 
#define __obfs_42d6c7d61481d__ 0; 
#define __obfs_5607fe8879__ } 
#define __obfs_db1915052d15f781__ void 
#define __obfs_253f__ compute_num(int 
#define __obfs_3fb451__ **plants, 
#define __obfs_df12ecd07__ int 
#define __obfs_471c75__ rows, 
#define __obfs_8c00dee24c987__ int 
#define __obfs_e60e81c4cb__ columns) 
#define __obfs_5cce8dede__ { 
#define __obfs_109d2__ for 
#define __obfs_aa48__ (int 
#define __obfs_cb8acb1dc9821bf__ i 
#define __obfs_99ad__ = 
#define __obfs_0804083__ 0; 
#define __obfs_35309226eb45ec__ i 
#define __obfs_d63fbf8c31737__ < 
#define __obfs_748ba69d3e__ rows; 
#define __obfs_b5a1fc208598603__ i++) 
#define __obfs_d1a__ for 
#define __obfs_b60c5a__ (int 
#define __obfs_17e__ j 
#define __obfs_cda72177eba360f__ = 
#define __obfs_1373b2__ 0; 
#define __obfs_d01__ j 
#define __obfs_819c9fbfb0__ < 
#define __obfs_f337d999d9__ columns; 
#define __obfs_89ae0__ j++) 
#define __obfs_aff0a6a45212329__ { 
#define __obfs_204da25__ switch 
#define __obfs_35464c__ (plants[i][j]) 
#define __obfs_c88d8d0a60977__ { 
#define __obfs_6b8eba43__ case 
#define __obfs_4e6cd95227cb__ SUNFLOWER: 
#define __obfs_351b33587c5fdd__ this->sunflower++; 
#define __obfs_18e__ break; 
#define __obfs_9898__ case 
#define __obfs_b2dd140336c9d__ WINTERPEASHOOTER: 
#define __obfs_4e9cec__ this->winterpeashooter++; 
#define __obfs_596f713f9a737__ break; 
#define __obfs_2992__ case 
#define __obfs_020c8bfac__ PEASHOOTER: 
#define __obfs_3a20f62a0af1aa1__ this->peashooter++; 
#define __obfs_b132ecc1609b__ break; 
#define __obfs_92af__ case 
#define __obfs_4d6e4749__ SMALLNUT: 
#define __obfs_facf9f74__ this->smallnut++; 
#define __obfs_d961__ break; 
#define __obfs_be53ee611049__ case 
#define __obfs_18d10dc__ PEPPER: 
#define __obfs_dfa92d8f817__ this->pepper++; 
#define __obfs_655__ break; 
#define __obfs_794__ case 
#define __obfs_7bd28f15a49d5e5__ SQUASH: 
#define __obfs_45____ this->squash++; 
#define __obfs_a1af__ break; 
#define __obfs_0d4f480__ } 
#define __obfs_70ef__ } 
#define __obfs_af__ } 
#define __obfs_7e1d842d0f7__ }; 
#define __obfs_95__ int 
#define __obfs_ed4227734ed__ calculate_zombie_nums(int 
#define __obfs_dc____ ***zombies, 
#define __obfs_88a1__ int 
#define __obfs_b71091__ rows, 
#define __obfs_076023__ int 
#define __obfs_27728__ columns) 
#define __obfs_228499b55310264a__ { 
#define __obfs_8f__ int 
#define __obfs_49a__ num 
#define __obfs_894b77f805bd94__ = 
#define __obfs_dca5672f__ 0; 
#define __obfs_bcb41ccdc4363c__ for 
#define __obfs_5129a5ddcd0dcd7__ (int 
#define __obfs_d72fbbccd9f__ i 
#define __obfs_06a81a4fb98d1__ = 
#define __obfs_0ebcc77dc72360d__ 0; 
#define __obfs_d88518__ i 
#define __obfs_309fee4e5__ < 
#define __obfs_87ec2f451208__ rows; 
#define __obfs_9c19a2aa1d8__ i++) 
#define __obfs_83e8ef5__ { 
#define __obfs_9e984c10815__ for 
#define __obfs_c559da2ba96__ (int 
#define __obfs_1bc02__ j 
#define __obfs_f3173935ed8ac__ = 
#define __obfs_a368b0__ 0; 
#define __obfs_f18a6d1cde4b205__ j 
#define __obfs_495dabfd0ca768__ < 
#define __obfs_959735__ columns; 
#define __obfs_faafda66202d2344__ j++) 
#define __obfs_a2cc63e06__ { 
#define __obfs_a14ac55__ int 
#define __obfs_7a6a74cbe87bc__ k 
#define __obfs_52947e0ade57a__ = 
#define __obfs_69d658__ 0; 
#define __obfs_e9fd__ while 
#define __obfs_71a58e__ (zombies[i][j][k] 
#define __obfs_962e56a8__ != 
#define __obfs_297__ -1) 
#define __obfs_f60bb6bb4c96d4df__ { 
#define __obfs_d1dc3a8270a6f9__ num++; 
#define __obfs_806beafe1__ k++; 
#define __obfs_4462bf0ddb__ } 
#define __obfs_c7a__ } 
#define __obfs_fc528592c385__ } 
#define __obfs_93__ return 
#define __obfs_a981f2b70__ num; 
#define __obfs_bc573864331a9__ } 
#define __obfs_97d0145823__ int 
#define __obfs_efb76cff97__ choose_Lines_not_Broken(int 
#define __obfs_5c50b4df4b1768__ *Left_lines, 
#define __obfs_46031b3d04dc909__ int 
#define __obfs_6ba__ **plants, 
#define __obfs_0771fc6f0f4__ int 
#define __obfs_21fe5b8ba755eea__ column) 
#define __obfs_6dd4e10e3296fa63__ { 
#define __obfs_42a396__ for 
#define __obfs_1c54__ (int 
#define __obfs_52c5__ i 
#define __obfs_7e230522657__ = 
#define __obfs_3c1e4bd671__ 0; 
#define __obfs_84f0f20__ ; 
#define __obfs_10c272d06794d3__ i++) 
#define __obfs_81c650caac28c__ { 
#define __obfs_f670ef5d2d6__ if 
#define __obfs_89f03f7d02__ (Left_lines[i] 
#define __obfs_c1fea270c__ == 
#define __obfs_e4873aa9a0__ 1 
#define __obfs_8d420f__ && 
#define __obfs_7437d136770f5b3__ plants[i][column] 
#define __obfs_96de2547__ == 
#define __obfs_973a5f0ccb__ NOPLANT) 
#define __obfs_be3e9d3f7d705__ return 
#define __obfs_207f880__ i; 
#define __obfs_b147__ } 
#define __obfs_9d2682367c3935__ return 
#define __obfs_cc___ rand() 
#define __obfs_712a3c9__ % 
#define __obfs_a40511cad8383e5__ ROW; 
#define __obfs_c0560792e4__ } 
#define __obfs_e16960__ typedef 
#define __obfs_9a4400__ struct 
#define __obfs_7d12b66d3df6af8d__ pos_and_value 
#define __obfs_b2531e__ { 
#define __obfs_e449b9317da__ int 
#define __obfs_4f398cb9d6bc7__ pos[2]; 
#define __obfs_e8d92f99e__ double 
#define __obfs_86d7c8a08b4aaa1b__ value; 
#define __obfs_15__ } 
#define __obfs_b0f2ad44d26e1a6f__ pos_and_value; 
#define __obfs_cd___ class 
#define __obfs_148__ value_plant_func 
#define __obfs_647c7__ { 
#define __obfs_24____ public: 
#define __obfs_a0f__ double 
#define __obfs_757f843a169__ noplant; 
#define __obfs_64f1f27bf1b4e__ pos_and_value 
#define __obfs_831c2f8__ sunflower; 
#define __obfs_08e6be__ pos_and_value 
#define __obfs_2cb6b10338a7fc__ peashooter; 
#define __obfs_e638471149171__ pos_and_value 
#define __obfs_11d0e6287202__ winterpeashooter; 
#define __obfs_f50a6c02a3fc5a__ pos_and_value 
#define __obfs_6a816__ smallnut; 
#define __obfs_fd__ pos_and_value 
#define __obfs_1ef91c212e__ pepper; 
#define __obfs_5d__ pos_and_value 
#define __obfs_b618c3210e__ squash; 
#define __obfs_7fea637fd__ int 
#define __obfs_ae614c557__ generating_row; 
#define __obfs_7c4ede__ IPlayer 
#define __obfs_d43ab110ab__ *player; 
#define __obfs_8303a79b1e19a__ Game 
#define __obfs_4921f95ba__ game; 
#define __obfs_b59a51a3c0bf9c__ int 
#define __obfs_26751be11814__ NotBrokenLinesNum; 
#define __obfs_e721a54a8cf1__ int 
#define __obfs_5cf21ce__ KillZombiesScore; 
#define __obfs_673271cc47c1a4__ int 
#define __obfs_9f__ LeftPlants; 
#define __obfs_ef2a4be5473__ int 
#define __obfs_01e00f2f4bfcbb75__ Score; 
#define __obfs_15231a7ce4ba789__ int 
#define __obfs_b9f94c77652c__ time; 
#define __obfs_375c__ int 
#define __obfs_a588a6__ *PlaceCD; 
#define __obfs_2a27b8144ac02f67__ int 
#define __obfs_8bb88f80d__ **Plants; 
#define __obfs_02f0__ int 
#define __obfs_c59b469__ ***Zombies; 
#define __obfs_52d080a3e172c33__ int 
#define __obfs_5a142__ *LeftLines; 
#define __obfs_a941493ee__ int 
#define __obfs_a51c896c__ Sun; 
#define __obfs_464d__ int 
#define __obfs_798e__ zombie_nums; 
#define __obfs_0efbe98067__ value_plant_func(int 
#define __obfs_66be31e4__ NotBrokenLinesNum, 
#define __obfs_8b5__ int 
#define __obfs_fc6709__ KillZombiesScore, 
#define __obfs_f3144cefe8__ int 
#define __obfs_acab011__ Score, 
#define __obfs_28dc6b0__ int 
#define __obfs_404dcc9__ time, 
#define __obfs_8725fb777f__ int 
#define __obfs_62__ *PlaceCD, 
#define __obfs_3e7e02__ int 
#define __obfs_7456__ **Plants, 
#define __obfs_51___ int 
#define __obfs_7137debd45ae__ ***Zombies, 
#define __obfs_25e2a30__ int 
#define __obfs_851300ee84__ *LeftLines, 
#define __obfs_b29eed44276__ int 
#define __obfs_270edd69788d__ Sun, 
#define __obfs_4fa53be91b4933d__ IPlayer 
#define __obfs_ab2__ *player, 
#define __obfs_c4492cbe90fbdb__ Game 
#define __obfs_c0___ game) 
#define __obfs_70ece1e1e0931919__ { 
#define __obfs_84c6494d30851c__ this->NotBrokenLinesNum 
#define __obfs_752d25a1f8dbfb2__ = 
#define __obfs_54f__ NotBrokenLinesNum; 
#define __obfs_b3b43a__ this->KillZombiesScore 
#define __obfs_6e62__ = 
#define __obfs_955a158__ KillZombiesScore; 
#define __obfs_418ef6127e__ this->Score 
#define __obfs_97d9811903__ = 
#define __obfs_442cd__ Score; 
#define __obfs_3e15cc11f9__ this->time 
#define __obfs_54e36c5ff5__ = 
#define __obfs_fc9b003b__ time; 
#define __obfs_6a5dfac4b__ this->PlaceCD 
#define __obfs_b3bbccd6c0__ = 
#define __obfs_11c4__ PlaceCD; 
#define __obfs_a63fc8c5__ this->Plants 
#define __obfs_231141b34c8__ = 
#define __obfs_d8d31bd778da__ Plants; 
#define __obfs_ce__ this->Zombies 
#define __obfs_d2cdf047a66__ = 
#define __obfs_261__ Zombies; 
#define __obfs_ba1__ this->LeftLines 
#define __obfs_e22dd5dabde45ed__ = 
#define __obfs_7283518d47a0__ LeftLines; 
#define __obfs_17e___ this->Sun 
#define __obfs_df9028fcb6b0__ = 
#define __obfs_94e445__ Sun; 
#define __obfs_8698ff92115213a__ this->player 
#define __obfs_96a93__ = 
#define __obfs_e8fd4a8a5ba__ player; 
#define __obfs_db__ this->generating_row 
#define __obfs_7eb7eabbe9b__ = 
#define __obfs_e5a__ 1; 
#define __obfs_21be9a__ this->game 
#define __obfs_299570476__ = 
#define __obfs_4abe__ game; 
#define __obfs_f0bda__ } 
#define __obfs_36d7534290610d__ int 
#define __obfs_7dd0__ **sum_plants_per_row() 
#define __obfs_e9b73b__ { 
#define __obfs_6709e8d6__ int 
#define __obfs_8c01a75__ **plants_num_format 
#define __obfs_f63f65b503e2__ = 
#define __obfs_8b6a80c3cf2cbd__ (int 
#define __obfs_4a2ddf148c5a9__ **)malloc(ROW 
#define __obfs_b865367__ * 
#define __obfs_365d17770080c80__ sizeof(int 
#define __obfs_393c55aea738548__ *)); 
#define __obfs_6449f44a102__ for 
#define __obfs_d860bd1__ (int 
#define __obfs_db957c626a8cd7a2__ i 
#define __obfs_ecd62de20ea67e1__ = 
#define __obfs_d25414__ 0; 
#define __obfs_bf201d540__ i 
#define __obfs_052335232b1__ < 
#define __obfs_c8cbd__ ROW; 
#define __obfs_59e0b2658e9__ i++) 
#define __obfs_0731460__ { 
#define __obfs_9059__ plants_num_format[i] 
#define __obfs_8d__ = 
#define __obfs_ac5dab__ (int 
#define __obfs_0533a88__ *)malloc(sizeof(int) 
#define __obfs_f39ae9ff3a81f499__ * 
#define __obfs_cd14821dab__ PLANT_KIND); 
#define __obfs_dc40b7120e__ memset(plants_num_format[i], 
#define __obfs_3fab5__ 0, 
#define __obfs_90e13__ PLANT_KIND 
#define __obfs_7ffd85d93__ * 
#define __obfs_d1e946f4e67db__ sizeof(int)); 
#define __obfs_1f1baa5b8eda__ } 
#define __obfs_39027dfad5138__ for 
#define __obfs_64__ (int 
#define __obfs_6e79ed05baec2754__ i 
#define __obfs_09b1__ = 
#define __obfs_5b6ba13f79129__ 0; 
#define __obfs_f542eae1949358e2__ i 
#define __obfs_155fa0959__ < 
#define __obfs_f0b__ ROW; 
#define __obfs_faa__ i++) 
#define __obfs_f4a__ { 
#define __obfs_f5c3dd7514bf__ for 
#define __obfs_17c3433__ (int 
#define __obfs_f2__ j 
#define __obfs_59___ = 
#define __obfs_0e08__ 0; 
#define __obfs_14__ j 
#define __obfs_2647c1dba2__ < 
#define __obfs_ed519dacc8__ COLUMN; 
#define __obfs_f442d33fa068320__ j++) 
#define __obfs_fface8385abbf__ { 
#define __obfs_4496bf24afe__ switch 
#define __obfs_aa2a7737137409__ (this->Plants[i][j]) 
#define __obfs_06___ { 
#define __obfs_e0ab531ec3121__ case 
#define __obfs_61b1fb3f59__ SUNFLOWER: 
#define __obfs_9a1de__ plants_num_format[i][SUNFLOWER]++; 
#define __obfs_d757719ed7c2b66__ break; 
#define __obfs_dfce06__ case 
#define __obfs_f26dab9bf__ WINTERPEASHOOTER: 
#define __obfs_85f007f8c50dd__ plants_num_format[i][WINTERPEASHOOTER]++; 
#define __obfs_d7657583058__ break; 
#define __obfs_728f206c2a01b__ case 
#define __obfs_201d728__ PEASHOOTER: 
#define __obfs_e8dfff4__ plants_num_format[i][PEASHOOTER]++; 
#define __obfs_57c0531e13f4__ break; 
#define __obfs_4888241374e8c62__ case 
#define __obfs_06a15eb1c38367__ SMALLNUT: 
#define __obfs_59____ plants_num_format[i][SMALLNUT]++; 
#define __obfs_f45a1078feb35de__ break; 
#define __obfs_82cadb0649a3af4__ case 
#define __obfs_7385db9a3f114__ PEPPER: 
#define __obfs_cd____ plants_num_format[i][PEPPER]++; 
#define __obfs_8c__ break; 
#define __obfs_ff1418e8c__ case 
#define __obfs_eb1e78__ SQUASH: 
#define __obfs_7503cfa__ plants_num_format[i][SQUASH]++; 
#define __obfs_49ad__ break; 
#define __obfs_6ae07dcb33ec3b__ } 
#define __obfs_3c947bc2f7__ } 
#define __obfs_a3545bd79d31f9a__ } 
#define __obfs_d7fd1__ return 
#define __obfs_537de305e__ plants_num_format; 
#define __obfs_96c5c28be__ } 
#define __obfs_f9d__ void 
#define __obfs_4e87337f366f7__ beginning_operation() 
#define __obfs_09fb05__ { 
#define __obfs_d0__ if 
#define __obfs_69d__ (this->time 
#define __obfs_19de10adbaa1__ <= 
#define __obfs_a19acd7d2__ 2) 
#define __obfs_c164bbc9d6c7__ { 
#define __obfs_68c694__ this->player->PlacePlant(SUNFLOWER, 
#define __obfs_d305281faf947__ this->generating_row, 
#define __obfs_fb8feff253bb6__ 1); 
#define __obfs_2f25__ this->player->PlacePlant(SMALLNUT, 
#define __obfs_d4b2ae__ this->generating_row, 
#define __obfs_958adb57686__ COLUMN 
#define __obfs_7e9e346dc5fd268__ - 
#define __obfs_ba9a56ce0a9b__ 1); 
#define __obfs_f31b20466ae89__ } 
#define __obfs_dc5d637ed5e62c__ } 
#define __obfs_44a2e08__ void 
#define __obfs_3214a6d842cc__ GameState_2_50() 
#define __obfs_b4568df26__ { 
#define __obfs_e1____ if 
#define __obfs_c45__ (this->time 
#define __obfs_f0fcf351df4e__ > 
#define __obfs_d5237__ 2 
#define __obfs_c366c2c9__ && 
#define __obfs_7302e3f5e7c0__ this->time 
#define __obfs_2d1b__ < 
#define __obfs_6814859__ 200) 
#define __obfs_865dfbde8a344b__ { 
#define __obfs_1316__ int 
#define __obfs_ca4__ alarming_flag 
#define __obfs_56f9f8__ = 
#define __obfs_5fa9e41bfec0725__ -1; 
#define __obfs_059fdcd96baeb7__ for 
#define __obfs_e06f967fb0d3555__ (int 
#define __obfs_af33__ i 
#define __obfs_11f__ = 
#define __obfs_6be5336db2c11__ 0; 
#define __obfs_9fdb__ i 
#define __obfs_d54e99a6__ < 
#define __obfs_fc4ddc15f9f4b4b__ ROW; 
#define __obfs_94462__ i++) 
#define __obfs_c915__ { 
#define __obfs_73e0f74__ if 
#define __obfs_dea9ddb2__ (i 
#define __obfs_77369e37b2aa__ != 
#define __obfs_65699726a3c601__ this->generating_row) 
#define __obfs_0609154__ { 
#define __obfs_ab7314__ for 
#define __obfs_04df4d434d48__ (int 
#define __obfs_ff7d0f__ j 
#define __obfs_c44__ = 
#define __obfs_07a4e2__ 0; 
#define __obfs_b432f34c__ j 
#define __obfs_65fc52ed8f88__ < 
#define __obfs_cb79f8fa58b91__ COLUMN; 
#define __obfs_e7___ j++) 
#define __obfs_8c8a58fa97__ { 
#define __obfs_44968aece94f667e__ int 
#define __obfs_9f6992966__ k 
#define __obfs_333222170ab9edc__ = 
#define __obfs_414e773d5b7e5__ 0; 
#define __obfs_b139e104214a0__ while 
#define __obfs_0950ca92a4dcf4__ (this->Zombies[i][j][k] 
#define __obfs_5103c358__ != 
#define __obfs_e5__ -1) 
#define __obfs_5bce843d__ { 
#define __obfs_139f0874f2ded__ if 
#define __obfs_29530de21__ (j 
#define __obfs_15d185eaa__ < 
#define __obfs_52d__ 3) 
#define __obfs_1e913e1b06__ alarming_flag 
#define __obfs_8562ae5__ = 
#define __obfs_8d55a249e6ba__ i; 
#define __obfs_11108a3db__ if 
#define __obfs_13___ (this->Sun 
#define __obfs_ad4c__ >= 
#define __obfs_f22e4747da__ 70) 
#define __obfs_95e68__ switch 
#define __obfs_7af__ (this->Zombies[i][j][k]) 
#define __obfs_519__ { 
#define __obfs_c3395dd46c34f__ case 
#define __obfs_6f2688a5fce7d48c__ POLEVAULT: 
#define __obfs_2d00f43f07911355__ case 
#define __obfs_1f71e393b380919__ SLED: 
#define __obfs_de03__ this->player->PlacePlant(SQUASH, 
#define __obfs_7ca57a9f__ i, 
#define __obfs_36ac8e558ac769__ (j 
#define __obfs_03e7d2e__ - 
#define __obfs_6a508a__ 1 
#define __obfs_111__ < 
#define __obfs_a38b1__ 0 
#define __obfs_5a7f963e5e0504__ ? 
#define __obfs_378a0__ 0 
#define __obfs_e3__ : 
#define __obfs_27___ j 
#define __obfs_d77f0076__ - 
#define __obfs_e4dd5528f759__ 1)); 
#define __obfs_7f16109f1619fd7__ break; 
#define __obfs_f106b7f99d2cb30__ case 
#define __obfs_95f6870ff3dcd442__ BUCKET: 
#define __obfs_c215b44__ if 
#define __obfs_39dca__ (this->PlaceCD[SQUASH] 
#define __obfs_d46__ == 
#define __obfs_3683af9d6f6c__ 0) 
#define __obfs_a82d922b133be19__ this->player->PlacePlant(SQUASH, 
#define __obfs_98c724289__ i, 
#define __obfs_4d8556695c262a__ (j 
#define __obfs_0004d0b5__ - 
#define __obfs_de7399880268__ 1 
#define __obfs_c4de8ced__ < 
#define __obfs_deb54ffb__ 0 
#define __obfs_3d863__ ? 
#define __obfs_7d2b92b6726c__ 0 
#define __obfs_dd055f53a4570__ : 
#define __obfs_4afd521d__ j 
#define __obfs_405e289063__ - 
#define __obfs_798cebccb3__ 1)); 
#define __obfs_f80bf05527157a8c__ else 
#define __obfs_b3b4d2db__ if 
#define __obfs_fb87582__ (j 
#define __obfs_1e4d36177d71b__ < 
#define __obfs_1b3__ 3) 
#define __obfs_1f36c15d6a3d1__ this->player->PlacePlant(PEPPER, 
#define __obfs_8c___ i, 
#define __obfs_d68__ (j 
#define __obfs_9d7311b__ - 
#define __obfs_4a3e00961a08879c__ 1 
#define __obfs_dc513ea4fbdaa7a1__ < 
#define __obfs_960__ 0 
#define __obfs_d5c18698__ ? 
#define __obfs_c5a4e7e6882845e__ 0 
#define __obfs_008bd5ad93b754d5__ : 
#define __obfs_3f088ebeda035__ j 
#define __obfs_635__ - 
#define __obfs_06964dce__ 1)); 
#define __obfs_c5b2c__ break; 
#define __obfs_5ec829d__ case 
#define __obfs_08____ GARGANTUAR: 
#define __obfs_d0fb96__ this->player->PlacePlant(SQUASH, 
#define __obfs_4ba29__ i, 
#define __obfs_a59__ (j 
#define __obfs_b8b4__ - 
#define __obfs_d4__ 1 
#define __obfs_ea5a486c71__ < 
#define __obfs_a00e5eb097__ 0 
#define __obfs_ef8446f355__ ? 
#define __obfs_f1981e4bd8__ 0 
#define __obfs_d7a84628c02__ : 
#define __obfs_c8758b51708__ j 
#define __obfs_253614bb__ - 
#define __obfs_8038__ 1)); 
#define __obfs_cee8d6b__ if 
#define __obfs_65d2ea03425887a7__ (j 
#define __obfs_95192c9873238__ < 
#define __obfs_8d8__ 4) 
#define __obfs_84___ this->player->PlacePlant(PEPPER, 
#define __obfs_ea6b2efbdd4255a9__ i, 
#define __obfs_7b7a53e239400a13__ 8); 
#define __obfs_05a5cf06982ba__ break; 
#define __obfs_3a824154__ case 
#define __obfs_5531a58348__ NORMAL: 
#define __obfs_07811dc6c422__ this->player->PlacePlant(PEASHOOTER, 
#define __obfs_312__ i, 
#define __obfs_c92a1032__ 1); 
#define __obfs_9f62b8625f914a0__ this->player->PlacePlant(SMALLNUT, 
#define __obfs_d860edd1dd83b3__ i, 
#define __obfs_093b60fd0557__ (j 
#define __obfs_2d579__ - 
#define __obfs_88ef51f0__ 1 
#define __obfs_5352696a9ca3__ < 
#define __obfs_a5a6171__ 0 
#define __obfs_d198bd736a97e7c__ ? 
#define __obfs_2b0f658cbf__ 0 
#define __obfs_f48c04ffa__ : 
#define __obfs_23d2e1578544b1__ j 
#define __obfs_2557911c1__ - 
#define __obfs_a48564053b3c7b54__ 1)); 
#define __obfs_4c144c47ec__ break; 
#define __obfs_89885ff2__ } 
#define __obfs_71e09b16e21f7b6__ k++; 
#define __obfs_d79c__ } 
#define __obfs_d8330f857a1__ } 
#define __obfs_0189caa5525__ } 
#define __obfs_38751__ else 
#define __obfs_a501bebf79__ for 
#define __obfs_051928341__ (int 
#define __obfs_06b1338ba02add__ j 
#define __obfs_aebf7782a3d445__ = 
#define __obfs_a9813e9550fe__ 0; 
#define __obfs_584b98aac2ddd__ j 
#define __obfs_f3e52c300b822__ < 
#define __obfs_955c__ COLUMN; 
#define __obfs_9a___ j++) 
#define __obfs_a96d3afec__ { 
#define __obfs_df4fe__ int 
#define __obfs_1359aa93__ k 
#define __obfs_2eace51d__ = 
#define __obfs_f8c0c96863284__ 0; 
#define __obfs_52dbb0686f8bd0c__ while 
#define __obfs_2d405b367158e3__ (this->Zombies[this->generating_row][j][k] 
#define __obfs_16ba72172__ != 
#define __obfs_f8bf09__ -1) 
#define __obfs_0ae3f79a302__ { 
#define __obfs_6f492___ if 
#define __obfs_b5f1e8fb36cd7fbe__ (this->Sun 
#define __obfs_814a9c1__ >= 
#define __obfs_325995af77a0e8b0__ 70) 
#define __obfs_296472c9542ad__ switch 
#define __obfs_fb2e203__ (this->Zombies[this->generating_row][j][k]) 
#define __obfs_07cb5f86508f146__ { 
#define __obfs_4b86abe48d3__ case 
#define __obfs_1f4fe6a4411__ POLEVAULT: 
#define __obfs_cbef4632102__ case 
#define __obfs_6492d3__ BUCKET: 
#define __obfs_819e3d6__ case 
#define __obfs_f4105__ SLED: 
#define __obfs_654ad60__ this->player->PlacePlant(SQUASH, 
#define __obfs_54ff9e__ this->generating_row, 
#define __obfs_0070d23__ 5); 
#define __obfs_850af92f__ break; 
#define __obfs_3e9e39fed3__ case 
#define __obfs_a0__ GARGANTUAR: 
#define __obfs_e0a209__ this->player->PlacePlant(SQUASH, 
#define __obfs_f80ff32e08a25270__ this->generating_row, 
#define __obfs_4d6b3e38b9526002__ (j 
#define __obfs_d3a7__ - 
#define __obfs_bf424cb7b0dea0__ 1 
#define __obfs_26f5b__ < 
#define __obfs_0b1ec366924b26f__ 0 
#define __obfs_801__ ? 
#define __obfs_b2ab001909a8a6f0__ 0 
#define __obfs_cf2226ddd41b1a2d__ : 
#define __obfs_2c__ j 
#define __obfs_194cf6c2de8e0__ - 
#define __obfs_a03fa30821986df__ 1)); 
#define __obfs_a1d7311f2a__ if 
#define __obfs_978d76676f__ (j 
#define __obfs_2cad8fa47bbef__ < 
#define __obfs_c586__ 4) 
#define __obfs_8232e119d8f59aa8__ this->player->PlacePlant(PEPPER, 
#define __obfs_7b__ this->generating_row, 
#define __obfs_e7e23__ 8); 
#define __obfs_24f0d2c__ break; 
#define __obfs_c6335734d__ case 
#define __obfs_9185f3ec5__ NORMAL: 
#define __obfs_931af58__ this->player->PlacePlant(SMALLNUT, 
#define __obfs_05546b0e38__ this->generating_row, 
#define __obfs_c353__ (j 
#define __obfs_1a0a283b__ - 
#define __obfs_a2___ 1 
#define __obfs_01931a69__ < 
#define __obfs_51174add1__ 0 
#define __obfs_bdc4626aa1d1__ ? 
#define __obfs_4ba__ 1 
#define __obfs_3937230de3c8041__ : 
#define __obfs_92b__ j 
#define __obfs_1b5230e3ea6d__ - 
#define __obfs_44cd7a8f7f9f851__ 1)); 
#define __obfs_02b1__ break; 
#define __obfs_abdbeb4d__ } 
#define __obfs_5a1e3__ if 
#define __obfs_ef41d488755367__ (j 
#define __obfs_a012869311d64a__ < 
#define __obfs_3b92d__ (this->sum_plants_per_row())[this->generating_row][SUNFLOWER] 
#define __obfs_5227b6__ + 
#define __obfs_bd5af7cd9__ 1 
#define __obfs_cd4bb35c__ + 
#define __obfs_f15d337c7__ 1 
#define __obfs_a869ccbcbd9568__ && 
#define __obfs_f6e79__ this->PlaceCD[SQUASH] 
#define __obfs_c902b497eb972__ != 
#define __obfs_fca0789e__ 0) 
#define __obfs_9a49a25d845a4__ { 
#define __obfs_4e6__ this->player->PlacePlant(PEPPER, 
#define __obfs_9bb6dee__ i, 
#define __obfs_19____ 8); 
#define __obfs_37d0__ } 
#define __obfs_23c97e9cb93576e4__ k++; 
#define __obfs_5d6646aad9bcc0be__ } 
#define __obfs_2a34a__ } 
#define __obfs_9f44e95__ } 
#define __obfs_7dc1c76__ this->player->PlacePlant(SUNFLOWER, 
#define __obfs_c182f930a__ this->generating_row, 
#define __obfs_936a40b7e8ee__ (this->sum_plants_per_row())[this->generating_row][SUNFLOWER] 
#define __obfs_0d73a25092e5__ + 
#define __obfs_e21e4e58ad9ab5__ 1); 
#define __obfs_d3096__ if 
#define __obfs_24917db15c__ (alarming_flag 
#define __obfs_350db0__ != 
#define __obfs_a486cd__ -1) 
#define __obfs_cb8__ { 
#define __obfs_1e8c391a__ if 
#define __obfs_a381c2c35c9157f__ (this->PlaceCD[SQUASH] 
#define __obfs_ee26fc6__ == 
#define __obfs_d542599794c1c__ 0) 
#define __obfs_697e382cfd__ { 
#define __obfs_ddd9dda6bfaf__ this->player->PlacePlant(SQUASH, 
#define __obfs_1819__ alarming_flag, 
#define __obfs_33___ COLUMN 
#define __obfs_86e78499ee__ - 
#define __obfs_6e5025cc__ 1); 
#define __obfs_c3e403__ } 
#define __obfs_8929c70f8d710e41__ else 
#define __obfs_32e0561__ this->player->PlacePlant(PEPPER, 
#define __obfs_2596a54cdbb555c__ alarming_flag, 
#define __obfs_41e76__ COLUMN 
#define __obfs_bd0cc810b580__ - 
#define __obfs_88a839f2f__ 1); 
#define __obfs_f8e59f4__ } 
#define __obfs_9978b7063e297d8__ } 
#define __obfs_7bc__ } 
#define __obfs_d1a21da__ void 
#define __obfs_211c1e0b83b9c__ GameState_50_200() 
#define __obfs_0234c510bc6d9__ { 
#define __obfs_bb1662b7c5f22a0__ if 
#define __obfs_169779d3852b__ (this->time 
#define __obfs_12b1e42dc074__ > 
#define __obfs_3a1dd983__ 50 
#define __obfs_100d9f30ca54b1__ && 
#define __obfs_d51b__ this->time 
#define __obfs_2056d__ < 
#define __obfs_00a03ec65__ 200) 
#define __obfs_f1__ { 
#define __obfs_81b3833e2__ if 
#define __obfs_e2ad76f2326__ (this->Sun 
#define __obfs_b440509a0106086a__ >= 
#define __obfs_1c6a0198177bfc__ 400) 
#define __obfs_0a87257e53__ this->player->PlacePlant(WINTERPEASHOOTER, 
#define __obfs_71560ce98c82__ this->generating_row, 
#define __obfs_14ea0d5b0c__ 0); 
#define __obfs_ca___ } 
#define __obfs_cdf1e288ca02__ } 
#define __obfs_8c5f6ecd__ void 
#define __obfs_25__ value_peashooter_origin() 
#define __obfs_ea119a40__ { 
#define __obfs_6832a7b24b__ if 
#define __obfs_1145a30ff80__ (this->time 
#define __obfs_5249__ > 
#define __obfs_e45823af__ 50) 
#define __obfs_dd28e506350__ if 
#define __obfs_2d969e__ (this->PlaceCD[PEASHOOTER] 
#define __obfs_4b4edc2630fe__ == 
#define __obfs_06d5ae105__ 0) 
#define __obfs_fea9__ { 
#define __obfs_4aecfbe5__ double 
#define __obfs_cd3afef9__ **loss 
#define __obfs_db11__ = 
#define __obfs_1368ba1ab6ed38__ (double 
#define __obfs_3323fe11e9595c09__ **)malloc(ROW 
#define __obfs_05a70454516__ * 
#define __obfs_01894d6f048__ sizeof(double 
#define __obfs_f3d9de86462__ *)); 
#define __obfs_02e656ade__ for 
#define __obfs_5938b4d0__ (int 
#define __obfs_b5c01503041b7__ i 
#define __obfs_b0df2270be9cb16c__ = 
#define __obfs_13111c20ae__ 0; 
#define __obfs_d2a27e83d4__ i 
#define __obfs_598920e1__ < 
#define __obfs_934b535800__ ROW; 
#define __obfs_04048aeca2c0__ i++) 
#define __obfs_8ca8da41__ { 
#define __obfs_443de__ loss[i] 
#define __obfs_01eee509ee2f68dc__ = 
#define __obfs_efdf562ce2fb0ad4__ (double 
#define __obfs_4ae67__ *)malloc(COLUMN 
#define __obfs_6cd9313ed34__ * 
#define __obfs_32__ sizeof(double)); 
#define __obfs_2a8a812400df89__ memset(loss[i], 
#define __obfs_3e626__ 0, 
#define __obfs_e0f7a4d0ef9b84b__ COLUMN 
#define __obfs_653a__ * 
#define __obfs_b0b79da57b95__ sizeof(double)); 
#define __obfs_3dd9424__ } 
#define __obfs_b166b57d1__ double 
#define __obfs_29523510979__ max 
#define __obfs_487d4__ = 
#define __obfs_d4dd1__ -10000, 
#define __obfs_b6e3__ max_index[2] 
#define __obfs_1a3f91fead97497b__ = 
#define __obfs_90aef9__ {0, 
#define __obfs_3147da8ab4a__ 0}; 
#define __obfs_109__ for 
#define __obfs_758a06618c69880__ (int 
#define __obfs_df1f1d20ee8670__ i 
#define __obfs_be6__ = 
#define __obfs_243f__ 0; 
#define __obfs_a07c2f3b3b__ i 
#define __obfs_d5e2c0adad503c91__ < 
#define __obfs_6354__ ROW; 
#define __obfs_ce6c92303f38__ i++) 
#define __obfs_38651c4450f873__ for 
#define __obfs_c2ba1bc54b239__ (int 
#define __obfs_f6c79f4af47863__ j 
#define __obfs_d6__ = 
#define __obfs_2d__ 0; 
#define __obfs_04ad563202__ j 
#define __obfs_4cb811134b9d39f__ < 
#define __obfs_bbaa9d6a1445__ COLUMN; 
#define __obfs_0233f3b__ j++) 
#define __obfs_26505e0__ { 
#define __obfs_ccbd8ca962__ if 
#define __obfs_66e8ba821__ (this->Plants[i][j] 
#define __obfs_eb76c035d5__ != 
#define __obfs_53___ NOPLANT) 
#define __obfs_2b8eba3cb0d0f__ loss[i][j] 
#define __obfs_51de85ddd068f0b__ = 
#define __obfs_cd0f7__ -10000; 
#define __obfs_a376033f78e14__ else 
#define __obfs_743394b__ { 
#define __obfs_074177d3eb__ double 
#define __obfs_95f8d9901ca887__ row 
#define __obfs_cd0cbcc668fe4bc__ = 
#define __obfs_6150ccc606__ (i 
#define __obfs_fe40fb9__ == 
#define __obfs_cc7e2b878868c__ this->generating_row 
#define __obfs_9667150__ ? 
#define __obfs_dc16622ddc767e__ -10 
#define __obfs_0f46c64b7__ : 
#define __obfs_d6bcb486f7__ 0); 
#define __obfs_716e1b8c6cd17b77__ loss[i][j] 
#define __obfs_80537a945c7aaa78__ += 
#define __obfs_ae1eaa32d10b6c88__ row; 
#define __obfs_fa243__ double 
#define __obfs_5b8e4fd39d97862__ column 
#define __obfs_c36__ = 
#define __obfs_43351f7bf9a215__ (25); 
#define __obfs_1177__ loss[i][j] 
#define __obfs_98e6f1720902__ += 
#define __obfs_478__ column 
#define __obfs_5f6371c9__ * 
#define __obfs_229754d77991__ exp(-column) 
#define __obfs_16026d6__ - 
#define __obfs_130f1a8e9__ 10; 
#define __obfs_e069ea__ double 
#define __obfs_3de568f8__ zombie[ZOMBIE_KIND] 
#define __obfs_40b5f25a22857__ = 
#define __obfs_46a558d97__ {6, 
#define __obfs_2b45c629e57__ -10, 
#define __obfs_ffedf5be__ -2, 
#define __obfs_d827f12e3__ -40, 
#define __obfs_e6c2dc3dee4__ -20}; 
#define __obfs_2d2__ for 
#define __obfs_f976__ (int 
#define __obfs_6211080fa89__ column0 
#define __obfs_e58aea6__ = 
#define __obfs_f516dfb84b9__ 0; 
#define __obfs_49c0b9d84c2a16f__ j 
#define __obfs_046ddf96__ < 
#define __obfs_69dafe8b580664__ COLUMN; 
#define __obfs_f3ac63c91272__ j++) 
#define __obfs_db9e__ { 
#define __obfs_88bfc__ int 
#define __obfs_778609db5dc7e1a__ k 
#define __obfs_68d30981254__ = 
#define __obfs_426f99__ 0; 
#define __obfs_a11f__ while 
#define __obfs_a70dc40__ (Zombies[i][column0][k] 
#define __obfs_761c7920f470038d__ != 
#define __obfs_228b__ -1) 
#define __obfs_1498__ { 
#define __obfs_d5e__ loss[i][j] 
#define __obfs_6c97cd07663b0__ += 
#define __obfs_f1e__ zombie[Zombies[i][column0][k] 
#define __obfs_03255088ed6335__ - 
#define __obfs_fd69dbe2__ 1] 
#define __obfs_be53d253d6bc__ / 
#define __obfs_619205da514e83f__ (+COLUMN 
#define __obfs_273448411d__ - 
#define __obfs_e77dbaf67__ j); 
#define __obfs_f7__ k++; 
#define __obfs_7e3b7a5bafcb0f__ } 
#define __obfs_7b4773c0__ } 
#define __obfs_a3eb043e7__ double 
#define __obfs_806fec5af__ plant[PLANT_KIND] 
#define __obfs_b6cda1__ = 
#define __obfs_359__ {2, 
#define __obfs_43e4e6a6f341e006__ 0, 
#define __obfs_c8dfece5cc682492__ -2, 
#define __obfs_2321994d85__ 5, 
#define __obfs_7cc532d783a7__ 2, 
#define __obfs_f52854__ 0}; 
#define __obfs_81b073__ for 
#define __obfs_777669af68dbcc__ (int 
#define __obfs_b2397517665__ column0 
#define __obfs_20c9f__ = 
#define __obfs_70fcb77e63__ 0; 
#define __obfs_326a8c055c0__ j 
#define __obfs_0abdc563a06__ < 
#define __obfs_92049d__ COLUMN; 
#define __obfs_23af4__ j++) 
#define __obfs_d254c8a0__ { 
#define __obfs_3f53d7190148675__ if 
#define __obfs_ea204361__ (this->Plants[i][column0] 
#define __obfs_d095a94d20dc__ != 
#define __obfs_d20be76a86c0d__ NOPLANT) 
#define __obfs_d6911__ loss[i][j] 
#define __obfs_4ebd440d99504__ += 
#define __obfs_794288f252f45__ plant[this->Plants[i][column0]] 
#define __obfs_8aec5__ * 
#define __obfs_505259__ (1 
#define __obfs_f7e2b2b75b041756__ + 
#define __obfs_9fb__ (column0 
#define __obfs_d3b__ - 
#define __obfs_300891a621__ COLUMN 
#define __obfs_466accbac9a66b__ / 
#define __obfs_ab8aa05e78248__ 2) 
#define __obfs_ca43108ded__ / 
#define __obfs_0a65e19__ 40); 
#define __obfs_4c5bcfec__ } 
#define __obfs_5f146156__ double 
#define __obfs_8cbd005a556cc__ time_rate 
#define __obfs_123b7f02433572__ = 
#define __obfs_6ee69d3769__ 30; 
#define __obfs_269d83__ loss[i][j] 
#define __obfs_3837a451cd0a__ += 
#define __obfs_add217938e07__ time_rate 
#define __obfs_da4902cb0b__ * 
#define __obfs_7b66b4f__ (1 
#define __obfs_ee8fe9093f__ / 
#define __obfs_3ba__ (1 
#define __obfs_ea159dc978__ + 
#define __obfs_1a6__ exp((+this->time 
#define __obfs_99f59c0842e83c8__ - 
#define __obfs_8b4224068a41c__ TOTAL_TIME 
#define __obfs_d04863f100d__ / 
#define __obfs_063e26c670d07bb__ 5) 
#define __obfs_999600eb275cc__ / 
#define __obfs_10__ 200)) 
#define __obfs_a554f__ - 
#define __obfs_52cf49fea5ff6658__ 0.5); 
#define __obfs_d0921d442ee91b__ } 
#define __obfs_b0904096885__ if 
#define __obfs_dcf6070a4ab__ (max 
#define __obfs_878d5691__ < 
#define __obfs_565030e1fce4e481__ loss[i][j]) 
#define __obfs_bc7f62145__ { 
#define __obfs_03cf87174debac__ max_index[0] 
#define __obfs_959ef477__ = 
#define __obfs_4dd__ i; 
#define __obfs_bd7db7397f__ max_index[1] 
#define __obfs_8208974663db__ = 
#define __obfs_b53477c2__ j; 
#define __obfs_de7092ba6df4276__ } 
#define __obfs_97416ac0__ } 
#define __obfs_7cac11e2f46ed46__ this->peashooter.pos[0] 
#define __obfs_b3f61131__ = 
#define __obfs_a6__ max_index[0]; 
#define __obfs_ddeebdeefdb7e7e__ this->peashooter.pos[1] 
#define __obfs_18___ = 
#define __obfs_72e6d32__ max_index[1]; 
#define __obfs_cb2c2041d97__ this->peashooter.value 
#define __obfs_e3ca0449fa__ = 
#define __obfs_5dec7070__ max; 
#define __obfs_ac1ad983e08ad330__ } 
#define __obfs_db60b9__ } 
#define __obfs_020bf2c45e7bb322__ bool 
#define __obfs_7993e11204b215b2__ have_type_of_zombies(int 
#define __obfs_e139c454239bfd__ *zombie, 
#define __obfs_be1df9a5d087249__ int 
#define __obfs_af5d5ef24__ type) 
#define __obfs_4a06d868d__ { 
#define __obfs_f836305__ int 
#define __obfs_c65d7bd70fe3e5e__ k 
#define __obfs_2aaa__ = 
#define __obfs_cc0991344c3d760__ 0; 
#define __obfs_a9365bd906e1132__ while 
#define __obfs_1f__ (zombie[k] 
#define __obfs_cbf871__ != 
#define __obfs_d16509f6eaca102__ -1) 
#define __obfs_0fe473396__ { 
#define __obfs_f708f0__ if 
#define __obfs_b1301141f__ (zombie[k] 
#define __obfs_5314b9674c86e3f__ == 
#define __obfs_6547__ type) 
#define __obfs_3cf2559725a9f__ return 
#define __obfs_fc79250f8c5__ true; 
#define __obfs_feecee9__ k++; 
#define __obfs_7a68443__ } 
#define __obfs_6048ff4e8cb07aa6__ return 
#define __obfs_24e27b869b66e9__ false; 
#define __obfs_7f__ } 
#define __obfs_9ed9328611fe3f45__ int 
#define __obfs_2f4fe03d777__ search_for_nearest_zombie(int 
#define __obfs_2c3ddf4__ ***zombie, 
#define __obfs_07a9d3fe__ int 
#define __obfs_61d77652c97ef__ row, 
#define __obfs_49d4b2fa__ int 
#define __obfs_2dbf2163__ column) 
#define __obfs_28b__ { 
#define __obfs_8c9f32e03aeb2e__ int 
#define __obfs_03__ nearest 
#define __obfs_b427426b8acd__ = 
#define __obfs_7cf64379eb6f29__ 0; 
#define __obfs_7e____ for 
#define __obfs_54b2b21af__ (int 
#define __obfs_8bdb5058__ j 
#define __obfs_e9412ee56438__ = 
#define __obfs_cf05968255451bde__ 0; 
#define __obfs_10c66082c1__ j 
#define __obfs_1843e35d41c__ < 
#define __obfs_70c445ee64b1__ COLUMN; 
#define __obfs_1e0a84051e6a4a73__ j++) 
#define __obfs_7b___ { 
#define __obfs_250413d2__ int 
#define __obfs_e82c4__ k 
#define __obfs_57bafb2c2dfeefba__ = 
#define __obfs_7cc234202e9__ 0; 
#define __obfs_d9ff90f4__ while 
#define __obfs_73f490f3f868__ (Zombies[row][j][k] 
#define __obfs_5e6bd7a69__ != 
#define __obfs_0bf727e907c5__ -1) 
#define __obfs_fec87a37c__ { 
#define __obfs_c8067ad193__ if 
#define __obfs_4c8c76b39__ (nearest 
#define __obfs_53f__ > 
#define __obfs_1f34004ebcb05__ j 
#define __obfs_b06b5541a__ - 
#define __obfs_6b5754d__ column) 
#define __obfs_f5__ nearest 
#define __obfs_2c6ae45a3e88aee__ = 
#define __obfs_b4baaff0e2__ j 
#define __obfs_ea4eb4__ - 
#define __obfs_bb03__ column; 
#define __obfs_6a4c__ k++; 
#define __obfs_7989eda__ } 
#define __obfs_34__ } 
#define __obfs_347665597cb__ return 
#define __obfs_01a068__ nearest; 
#define __obfs_46515dc__ } 
#define __obfs_8a20a8621978__ void 
#define __obfs_c30fb4dc55d801__ judge_Lines_not_broken(double 
#define __obfs_33bb8__ *final_choice) 
#define __obfs_12ffb096__ { 
#define __obfs_d9f__ for 
#define __obfs_9af76329c78__ (int 
#define __obfs_cd10c7f37618__ i 
#define __obfs_f7696a9b36__ = 
#define __obfs_3f998e713a6e__ 0; 
#define __obfs_696b35cc35e__ i 
#define __obfs_e7____ < 
#define __obfs_7884a9652e__ ROW; 
#define __obfs_8c1b6fa97c4288a__ i++) 
#define __obfs_87682805257e__ { 
#define __obfs_836__ if 
#define __obfs_30aaf34d6afd4b__ (LeftLines[i] 
#define __obfs_8db9264228dc48f__ == 
#define __obfs_4e02__ 0) 
#define __obfs_f8b932c70d0b2e6b__ { 
#define __obfs_831caa1b__ final_choice[i] 
#define __obfs_84b20b1f5a__ = 
#define __obfs_b06f50d1f89bd8__ -10000; 
#define __obfs_415e1af7ea95f8__ } 
#define __obfs_8d09e4b85c783c__ } 
#define __obfs_c5d__ } 
#define __obfs_6ef80__ void 
#define __obfs_4a8423d5e91fd__ value_peashooter() 
#define __obfs_070dbb6024b5ef__ { 
#define __obfs_4a1590df1__ if 
#define __obfs_0d7__ (this->time 
#define __obfs_a6___ > 
#define __obfs_31c__ 30) 
#define __obfs_9407c82__ { 
#define __obfs_23__ if 
#define __obfs_ba3e9b6a51__ (this->PlaceCD[PEASHOOTER] 
#define __obfs_6be93f7a__ == 
#define __obfs_82ca5dd156__ 0) 
#define __obfs_55a988d__ { 
#define __obfs_217c__ for 
#define __obfs_9824f9c__ (int 
#define __obfs_4de75__ i 
#define __obfs_7827d__ = 
#define __obfs_0747b9be4f9__ 0; 
#define __obfs_f7a__ i 
#define __obfs_40__ < 
#define __obfs_1bf0c59238dd24__ ROW; 
#define __obfs_2aedcba6__ i++) 
#define __obfs_9657__ { 
#define __obfs_e92d74ccacdc984__ if 
#define __obfs_c3a690be93__ (LeftLines[i] 
#define __obfs_1b1132__ == 
#define __obfs_f0__ 0) 
#define __obfs_9d28de8ff9__ { 
#define __obfs_92a0e__ for 
#define __obfs_86ecf__ (int 
#define __obfs_0e4a2c65bdad__ j 
#define __obfs_b21f9f98829dea9a__ = 
#define __obfs_8535__ 0; 
#define __obfs_921c2dc40d0__ j 
#define __obfs_4be5a36cbaca8a__ < 
#define __obfs_d7619beb6eb18__ COLUMN; 
#define __obfs_8c59__ j++) 
#define __obfs_5acdc9ca5d99ae6__ { 
#define __obfs_1d94108e907bb8__ int 
#define __obfs_16808__ k 
#define __obfs_2288f691__ = 
#define __obfs_b5baa9c__ 0; 
#define __obfs_eb___ while 
#define __obfs_59eb5dd36914c2__ (Zombies[i][j][k] 
#define __obfs_dbab2adc8f9d__ != 
#define __obfs_dbd22__ -1) 
#define __obfs_8169__ { 
#define __obfs_e6acf4b0f69f6f6e__ k++; 
#define __obfs_42fe880812__ } 
#define __obfs_dda04f9d6341__ if 
#define __obfs_48c3e__ (k 
#define __obfs_02f657d55e__ == 
#define __obfs_852c44ddc__ 1 
#define __obfs_283085d30e105__ && 
#define __obfs_c0e905__ Zombies[i][j][0] 
#define __obfs_60519c3dd2__ == 
#define __obfs_8f___ NORMAL 
#define __obfs_fecf__ && 
#define __obfs_ef1e491a7__ j 
#define __obfs_74__ >= 
#define __obfs_9457__ COLUMN 
#define __obfs_5b168fdba5ee5ea2__ - 
#define __obfs_17b3c70617__ 2) 
#define __obfs_309a8e73b__ { 
#define __obfs_7e83722522e8aeb__ this->player->PlacePlant(PEASHOOTER, 
#define __obfs_eaa52f3366768bc__ i, 
#define __obfs_92426b262d11b0ad__ 0); 
#define __obfs_36__ } 
#define __obfs_c57168a952__ else 
#define __obfs_ef0__ if 
#define __obfs_fb89fd138b10__ (k 
#define __obfs_743c41__ > 
#define __obfs_7876acb__ 0 
#define __obfs_978f__ && 
#define __obfs_18bb68e2b38e4__ (have_type_of_zombies(Zombies[i][j], 
#define __obfs_026a39ae63343c__ POLEVAULT) 
#define __obfs_ce75840__ || 
#define __obfs_453fad__ have_type_of_zombies(Zombies[i][j], 
#define __obfs_bd70364a8fc__ BUCKET)) 
#define __obfs_ed578__ && 
#define __obfs_4ebc__ Sun 
#define __obfs_50abc3e730e36b3__ < 
#define __obfs_32b___ 400 
#define __obfs_e02e__ && 
#define __obfs_6403675579f61145__ time 
#define __obfs_92f54963fc39__ < 
#define __obfs_880610a__ 500 
#define __obfs_d3fad7d3634__ && 
#define __obfs_a431d70133ef__ j 
#define __obfs_53c6de78244e9f__ < 
#define __obfs_d756d3d2b9dac7__ 4) 
#define __obfs_339a18def9898dd__ { 
#define __obfs_8dc5983b8c4ef1d8__ int 
#define __obfs_321cf86b4c9f__ start 
#define __obfs_1175defd0__ = 
#define __obfs_6aed000af__ 0; 
#define __obfs_5df07ec__ while 
#define __obfs_c4f796af__ (Plants[i][start] 
#define __obfs_a3d06db1f8c85b__ != 
#define __obfs_75e33da9b__ NOPLANT) 
#define __obfs_17f98ddf04__ { 
#define __obfs_40173ea48d__ start++; 
#define __obfs_8bd__ } 
#define __obfs_cc7090__ if 
#define __obfs_06fe1c234519f6__ (search_for_nearest_zombie(Zombies, 
#define __obfs_8e68c3c7bf1__ i, 
#define __obfs_f1748d6b0fd9__ start) 
#define __obfs_6412fef87392ae8c__ >= 
#define __obfs_e354fd90__ 1) 
#define __obfs_4de81d910__ { 
#define __obfs_8e065119c74efe3__ player->PlacePlant(PEASHOOTER, 
#define __obfs_8cff9bf6694dcc__ i, 
#define __obfs_dd__ start); 
#define __obfs_e113bb92c6939__ } 
#define __obfs_75__ } 
#define __obfs_fc03d482532__ } 
#define __obfs_b75bd27b5a4__ } 
#define __obfs_ed277964__ } 
#define __obfs_c61fb__ } 
#define __obfs_c60d__ } 
#define __obfs_06c284d3__ } 
#define __obfs_09a5e2a11b__ int 
#define __obfs_9a5748a2__ *rank(double 
#define __obfs_f21e__ *array, 
#define __obfs_f12f2b34a0c31742__ int 
#define __obfs_38181d9__ len) 
#define __obfs_f35a__ { 
#define __obfs_a7789e__ double 
#define __obfs_f2___ max 
#define __obfs_0b7e926154c12__ = 
#define __obfs_eb06b9db06012a__ array[0]; 
#define __obfs_30f8f6b940d1073__ int 
#define __obfs_d8bf84__ *serial_num 
#define __obfs_148260a1ce4fe4__ = 
#define __obfs_0c215f1942760__ (int 
#define __obfs_217e34__ *)malloc(len 
#define __obfs_7180cffd6a8e82__ * 
#define __obfs_e0688d139__ sizeof(int)); 
#define __obfs_1680e9fa7b__ for 
#define __obfs_b096577e26__ (int 
#define __obfs_18ad989__ i 
#define __obfs_358a__ = 
#define __obfs_1b9__ 0; 
#define __obfs_2417dc8af8570f__ i 
#define __obfs_98b418276d571e62__ < 
#define __obfs_90__ len; 
#define __obfs_daaaf13651380465__ i++) 
#define __obfs_e727f__ { 
#define __obfs_1102a326d5f7c__ serial_num[i] 
#define __obfs_7edccc6614__ = 
#define __obfs_5ac8bb8a7d7__ i; 
#define __obfs_0bed45bd5__ } 
#define __obfs_028ee724157b05d0__ for 
#define __obfs_f8___ (int 
#define __obfs_0e900ad84f63__ i 
#define __obfs_88___ = 
#define __obfs_a8__ 0; 
#define __obfs_a8___ i 
#define __obfs_d89a__ < 
#define __obfs_e97c864e8ac__ len 
#define __obfs_94aef38441e__ - 
#define __obfs_98___ 1; 
#define __obfs_220a7f__ i++) 
#define __obfs_dcda54__ { 
#define __obfs_f1___ for 
#define __obfs_84____ (int 
#define __obfs_7c4bf50b71550__ j 
#define __obfs_41ab1b__ = 
#define __obfs_3a0844cee4fc__ 0; 
#define __obfs_573__ j 
#define __obfs_b3__ < 
#define __obfs_577fd60255d4bb0f__ i; 
#define __obfs_f6185f0ef0__ j++) 
#define __obfs_110eec23201__ { 
#define __obfs_d790c9e6c0b5e02__ if 
#define __obfs_3bd401731__ (array[j] 
#define __obfs_cf9b2d__ < 
#define __obfs_dbbf603ff0__ array[j 
#define __obfs_dc2b690516158a87__ + 
#define __obfs_ab452534__ 1]) 
#define __obfs_fb4ab556bc42__ { 
#define __obfs_04__ double 
#define __obfs_f1____ swap 
#define __obfs_df0e0__ = 
#define __obfs_2e7ceec8361275c4__ array[j]; 
#define __obfs_220c77af02f__ array[j] 
#define __obfs_81c2f886f91e18f__ = 
#define __obfs_82___ array[j 
#define __obfs_2e7__ + 
#define __obfs_65f2a94c8c2d56d5__ 1]; 
#define __obfs_03fa2f7502f5f6__ array[j 
#define __obfs_5a99__ + 
#define __obfs_de594__ 1] 
#define __obfs_65fc__ = 
#define __obfs_bbeb0c1b1fd__ swap; 
#define __obfs_403ea2e__ int 
#define __obfs_b628386c9b924__ serial_swap 
#define __obfs_ff2c__ = 
#define __obfs_cdd96e__ serial_num[j]; 
#define __obfs_058d6f2fb__ serial_num[j] 
#define __obfs_ad47a008a2f806a__ = 
#define __obfs_7aee26__ serial_num[j 
#define __obfs_fa2e8c438__ + 
#define __obfs_362387__ 1]; 
#define __obfs_33267e5__ serial_num[j 
#define __obfs_c315f0320b7cd4ec__ + 
#define __obfs_64a08e5f1e6c39fa__ 1] 
#define __obfs_4bbdcc0e82__ = 
#define __obfs_b1c00bcd4__ serial_swap; 
#define __obfs_23fc4cb__ } 
#define __obfs_5e751896e527c86__ } 
#define __obfs_b7f1f29db7c2364__ } 
#define __obfs_421b3ac5__ return 
#define __obfs_08f38e043__ serial_num; 
#define __obfs_3614__ } 
#define __obfs_ec1f850d934f4__ void 
#define __obfs_7f7c351ee__ value_sunflower() 
#define __obfs_1d497__ { 
#define __obfs_47fd3c87f42f55d__ if 
#define __obfs_9ff7c9eb9d37f43__ (this->time 
#define __obfs_a4613e8d72__ > 
#define __obfs_5658__ 10) 
#define __obfs_96f2b50__ if 
#define __obfs_cdcb2f__ (this->PlaceCD[SUNFLOWER] 
#define __obfs_78f7d96ea21cca__ == 
#define __obfs_22b1f2e__ 0) 
#define __obfs_5a45828dead__ { 
#define __obfs_531db99c__ double 
#define __obfs_d37124c4c__ score[5] 
#define __obfs_868b__ = 
#define __obfs_1006ff__ {0, 
#define __obfs_d37b3ca__ 0, 
#define __obfs_fc192b0c0d270db__ 0, 
#define __obfs_030e65da2b1__ 0, 
#define __obfs_b2ea5e977c5fc__ 0}; 
#define __obfs_9dc372713683fd8__ judge_Lines_not_broken(score); 
#define __obfs_04___ for 
#define __obfs_1769__ (int 
#define __obfs_9a11883317fde__ i 
#define __obfs_d58e2__ = 
#define __obfs_7f1___ 0; 
#define __obfs_35c5__ i 
#define __obfs_b0be__ < 
#define __obfs_566a9968b436285__ ROW; 
#define __obfs_2b692__ i++) 
#define __obfs_f804d211__ { 
#define __obfs_98d8a23f__ for 
#define __obfs_370__ (int 
#define __obfs_045cf83ab07__ j 
#define __obfs_f75526659f310__ = 
#define __obfs_f499d34bd87b4__ 0; 
#define __obfs_44ac09ac6a14913__ j 
#define __obfs_a7a3d7__ < 
#define __obfs_d8e1344e27a5b08__ COLUMN; 
#define __obfs_92bf5e6240__ j++) 
#define __obfs_f565bb9e__ { 
#define __obfs_1cd138d0499a68__ if 
#define __obfs_4a5876b450b453__ (Plants[i][j] 
#define __obfs_6244b2ba9__ == 
#define __obfs_b4a721cfb62f5__ SUNFLOWER) 
#define __obfs_fd4f21f2556d__ score[i] 
#define __obfs_b1300291698eade__ -= 
#define __obfs_d478446__ 10; 
#define __obfs_ae587cfeea5ac21a__ if 
#define __obfs_60243__ (Plants[i][j] 
#define __obfs_ccd__ == 
#define __obfs_ae__ PEASHOOTER) 
#define __obfs_5be278a9e02bed__ score[i] 
#define __obfs_fb3f76858cb38__ += 
#define __obfs_2e0bff759d057e__ 50 
#define __obfs_d210cf373__ * 
#define __obfs_b19aa25ff__ (1 
#define __obfs_ec__ * 
#define __obfs_ad82140cafe81__ (exp(-j))); 
#define __obfs_12__ if 
#define __obfs_4191ef5f6c__ (Plants[i][j] 
#define __obfs_e465ae46b0705__ == 
#define __obfs_a7f592cef__ WINTERPEASHOOTER) 
#define __obfs_e27a949795bbe863__ score[i] 
#define __obfs_74378__ += 
#define __obfs_952c3ff98a__ 100 
#define __obfs_0d9095b__ * 
#define __obfs_0fc170ecbb8ff__ (1 
#define __obfs_a3788c8c64fd6__ * 
#define __obfs_2eb5657d37f474e__ (exp(-j))); 
#define __obfs_64c318216__ if 
#define __obfs_4ab52371762__ (Plants[i][j] 
#define __obfs_564645fb__ == 
#define __obfs_c0f971d8__ SMALLNUT) 
#define __obfs_765d5fb115a__ score[i] 
#define __obfs_d00__ += 
#define __obfs_b4fd1d2cb085390__ 100 
#define __obfs_66__ * 
#define __obfs_227f6afd3b7f__ (-0.01 
#define __obfs_f3b7e5d3e__ * 
#define __obfs_39d3__ (j 
#define __obfs_8e9__ - 
#define __obfs_f5b1b89d98b__ 5) 
#define __obfs_4e2a__ * 
#define __obfs_18____ (j 
#define __obfs_d53697441ef12__ - 
#define __obfs_28acfe2da49__ 5) 
#define __obfs_aee92f16efd522__ + 
#define __obfs_56cb94cb34617__ 1); 
#define __obfs_0172d2__ } 
#define __obfs_46f76a4bda9a9579__ } 
#define __obfs_b030afbb__ for 
#define __obfs_3fc2c__ (int 
#define __obfs_12311d05c9aa__ i 
#define __obfs_09b69adcd7cbae__ = 
#define __obfs_b1____ 0; 
#define __obfs_46b2644cbdf489fa__ i 
#define __obfs_07380__ < 
#define __obfs_4ea__ ROW; 
#define __obfs_2bc8ae25856bc__ i++) 
#define __obfs_ade5540__ for 
#define __obfs_9752d873fa71c19__ (int 
#define __obfs_6775a0635c30__ j 
#define __obfs_6e0e24295e8a__ = 
#define __obfs_353de__ 0; 
#define __obfs_d0bb8259__ j 
#define __obfs_5d75b9__ < 
#define __obfs_a78482ce76496f__ COLUMN; 
#define __obfs_d71fa38b648d__ j++) 
#define __obfs_381__ { 
#define __obfs_bf2fb7d1825a1df3__ int 
#define __obfs_6f1d0705__ k 
#define __obfs_4b29__ = 
#define __obfs_eb9fc349601c6__ 0; 
#define __obfs_fdf1bc5669e8f__ while 
#define __obfs_5a2756a3cb9c__ (Zombies[i][j][k] 
#define __obfs_221__ != 
#define __obfs_e833e042f5__ -1) 
#define __obfs_d3d80b656929a__ { 
#define __obfs_881c6e__ if 
#define __obfs_d3aeec875__ (Zombies[i][j][k] 
#define __obfs_3070e6addcd702cb__ == 
#define __obfs_1a6727__ NORMAL) 
#define __obfs_139738__ score[i] 
#define __obfs_449__ -= 
#define __obfs_42a6845a557be__ 10 
#define __obfs_a226e450e214f__ * 
#define __obfs_894db62f7b7a6ed__ (1 
#define __obfs_bd135462__ / 
#define __obfs_1ec3e7af38e__ (0.1 
#define __obfs_e6cbc650cd57__ + 
#define __obfs_ef0d17b3bdb4__ j)); 
#define __obfs_85690f81aadc1749__ if 
#define __obfs_80__ (Zombies[i][j][k] 
#define __obfs_1a99f6__ == 
#define __obfs_8b3bac1__ BUCKET) 
#define __obfs_e2c6__ score[i] 
#define __obfs_327708d__ -= 
#define __obfs_2650d6089a6d6__ 50 
#define __obfs_7e0a020__ * 
#define __obfs_efd7e9ed0e5e694__ (1 
#define __obfs_e6af4__ / 
#define __obfs_4f1f29888cabf5d4__ (0.1 
#define __obfs_12a1d073d5__ + 
#define __obfs_f076073__ j)); 
#define __obfs_a6db4ed04f162__ if 
#define __obfs_ec8b57b__ (Zombies[i][j][k] 
#define __obfs_c61f571dbd2fb949__ == 
#define __obfs_445__ POLEVAULT) 
#define __obfs_2ef35a8b78b5__ score[i] 
#define __obfs_c30__ -= 
#define __obfs_780965ae22ea6ae__ 30 
#define __obfs_e98741479a7b__ * 
#define __obfs_15cf76466b972647__ (1 
#define __obfs_1dba__ / 
#define __obfs_488c1e03__ (0.1 
#define __obfs_7f018eb7b301a666__ + 
#define __obfs_b4944963b5c83d54__ j)); 
#define __obfs_7a006957be65__ if 
#define __obfs_6fe13__ (Zombies[i][j][k] 
#define __obfs_9719a00ed0c5709d__ == 
#define __obfs_5b413__ GARGANTUAR) 
#define __obfs_6b8b__ score[i] 
#define __obfs_e8f2779682__ -= 
#define __obfs_6e3197aae9__ 100 
#define __obfs_25ef0d887bc__ * 
#define __obfs_332647f433a1__ (1 
#define __obfs_f9fd2624bee__ / 
#define __obfs_a57e8915461b83a__ (0.1 
#define __obfs_379a7ba015d8bf1c__ + 
#define __obfs_3c333aadfc3ee8e__ j)); 
#define __obfs_b8b9c74ac__ if 
#define __obfs_3144__ (Zombies[i][j][k] 
#define __obfs_9e82757e9a1c__ == 
#define __obfs_c7558e9d1f956b01__ SLED) 
#define __obfs_73b8170__ score[i] 
#define __obfs_b5__ -= 
#define __obfs_dba31bb5c7599__ 80 
#define __obfs_ef67f7c2d86__ * 
#define __obfs_c68c9c8258ea7d85__ (1 
#define __obfs_b31df__ / 
#define __obfs_17eb7ecc__ (0.1 
#define __obfs_e924517087669__ + 
#define __obfs_340a3904__ j)); 
#define __obfs_dfb84a11f431c__ k++; 
#define __obfs_f6c9dc70ecfd8__ } 
#define __obfs_6271faad__ } 
#define __obfs_465636eb4a7__ int 
#define __obfs_17____ sunflower_num_in_generating_row 
#define __obfs_6d19c113404ce__ = 
#define __obfs_a4666cd9e1ab0e4__ 0; 
#define __obfs_39536__ for 
#define __obfs_ac34ae1fda29b8fe__ (int 
#define __obfs_56c82ccd658e__ j 
#define __obfs_2b64__ = 
#define __obfs_90___ 0; 
#define __obfs_a36b0dcd1e__ j 
#define __obfs_6624b__ < 
#define __obfs_86c4a__ COLUMN; 
#define __obfs_c4294__ j++) 
#define __obfs_25766f01__ { 
#define __obfs_5dc126b503__ if 
#define __obfs_b6617980ce__ (Plants[this->generating_row][j] 
#define __obfs_ec7f346604f__ == 
#define __obfs_8fc__ SUNFLOWER) 
#define __obfs_42853a61b26__ sunflower_num_in_generating_row++; 
#define __obfs_6c9__ } 
#define __obfs_8e9304__ score[this->generating_row] 
#define __obfs_4b21cf96d4cf__ += 
#define __obfs_2a0f97f81755__ 100 
#define __obfs_6e__ * 
#define __obfs_0c1c995b77ea__ (1 
#define __obfs_892c3b1c6dccd5__ / 
#define __obfs_c9efe5f2__ (sunflower_num_in_generating_row 
#define __obfs_ad8e88__ + 
#define __obfs_15___ 1)); 
#define __obfs_e07bceab69529__ int 
#define __obfs_bc4e356fe__ *serial_num 
#define __obfs_02180771a__ = 
#define __obfs_1b79b52d1bf__ rank(score, 
#define __obfs_e2f9247929b__ ROW); 
#define __obfs_dc20d1211__ for 
#define __obfs_b4__ (int 
#define __obfs_db5cea26__ i 
#define __obfs_e2___ = 
#define __obfs_b91b1facf3__ 0 
#define __obfs_779efbd24d5a7e3__ ; 
#define __obfs_d1c37__ i 
#define __obfs_3e60e09c222f206c__ < 
#define __obfs_3b2d8f129ae2f408__ ROW; 
#define __obfs_b887d8__ i++) 
#define __obfs_60ad838__ { 
#define __obfs_1c303b0e__ int 
#define __obfs_65a31da7ede4dc9__ j 
#define __obfs_63f446__ = 
#define __obfs_62da8c91ce__ 0; 
#define __obfs_466473650__ while 
#define __obfs_6db291ac__ (Plants[serial_num[0]][j] 
#define __obfs_af44c4__ == 
#define __obfs_0f21f0349__ NOPLANT) 
#define __obfs_e3___ { 
#define __obfs_6788076842__ j++; 
#define __obfs_2e__ } 
#define __obfs_a2____ player->PlacePlant(SUNFLOWER, 
#define __obfs_2bd2e33__ serial_num[0], 
#define __obfs_9edcc1391c208ba0__ j); 
#define __obfs_2d71b2ae158c7c59__ } 
#define __obfs_aa6b7a__ } 
#define __obfs_9ff0525c64bf3d4__ } 
#define __obfs_a11ce019e96a4c6__ void 
#define __obfs_b1b04__ value_smallmnut() 
#define __obfs_1c___ { 
#define __obfs_275d7fb__ if 
#define __obfs_769675d7c11f33__ (this->PlaceCD[SMALLNUT] 
#define __obfs_ae1d2c2d__ == 
#define __obfs_faa453efd__ 0) 
#define __obfs_5848ad959__ if 
#define __obfs_f6b5f8c32c6__ (this->time 
#define __obfs_c5c1c__ > 
#define __obfs_24b__ 20) 
#define __obfs_58aa__ { 
#define __obfs_ec47a5de1eb__ double 
#define __obfs_cb12d__ score[ROW] 
#define __obfs_f404__ = 
#define __obfs_a0b83c02d720__ {0, 
#define __obfs_71887f__ 0, 
#define __obfs_a36e841c5__ 0, 
#define __obfs_e93028bdc1aacdf__ 0, 
#define __obfs_908c9a56__ 0}; 
#define __obfs_d806ca13ca3449__ judge_Lines_not_broken(score); 
#define __obfs_a43__ double 
#define __obfs_20479c788fb__ plants_score[7] 
#define __obfs_3a61__ = 
#define __obfs_5f268dfb__ {0, 
#define __obfs_a72__ 5, 
#define __obfs_c02f9de3c2f30__ 20, 
#define __obfs_ee16f__ 20, 
#define __obfs_22722a343513__ -7, 
#define __obfs_b1f62fa99de9f27a__ -1, 
#define __obfs_5a__ 0}; 
#define __obfs_41___ for 
#define __obfs_77e__ (int 
#define __obfs_51be2fed6c55f__ i 
#define __obfs_53a1320__ = 
#define __obfs_248024541dbda1d__ 0; 
#define __obfs_9a96a2c73c0d4__ i 
#define __obfs_a74c3b__ < 
#define __obfs_e4____ ROW; 
#define __obfs_9cb9ed4f35c__ i++) 
#define __obfs_c8862fc1a3272571__ { 
#define __obfs_09__ for 
#define __obfs_e5___ (int 
#define __obfs_2bd235c31__ j 
#define __obfs_0cdf61037d7053__ = 
#define __obfs_b922ede9c__ 0; 
#define __obfs_7edfd52220e__ j 
#define __obfs_a0ba2648acd23dc7__ < 
#define __obfs_2d95__ COLUMN; 
#define __obfs_0cd60efb__ j++) 
#define __obfs_8a56257ea05c7401__ { 
#define __obfs_272e11700558e2__ double 
#define __obfs_7b6__ distance_cost 
#define __obfs_03bfc1d478396__ = 
#define __obfs_4b86ca4__ 1; 
#define __obfs_10ce03a1ed01__ switch 
#define __obfs_a92c27__ (Plants[i][j]) 
#define __obfs_f0204e1d3ee3e4b0__ { 
#define __obfs_9023e__ case 
#define __obfs_9922f__ SUNFLOWER: 
#define __obfs_3fd60983292458bf__ distance_cost 
#define __obfs_fc325d4__ = 
#define __obfs_b8af__ 1.5 
#define __obfs_0ebf197205c00fc__ - 
#define __obfs_975e61077__ 0.05 
#define __obfs_8e489b4966fe8f7__ * 
#define __obfs_5d___ j; 
#define __obfs_4fa177df228645__ break; 
#define __obfs_ef72d5__ case 
#define __obfs_f0b1d5879866f2__ PEASHOOTER: 
#define __obfs_c1__ distance_cost 
#define __obfs_17754__ = 
#define __obfs_d9b1655__ 2 
#define __obfs_2836be05e71a__ - 
#define __obfs_dc6e224__ 0.09 
#define __obfs_c1502ae5a4d514b__ * 
#define __obfs_3f5ee243547__ j; 
#define __obfs_cc431fd7__ break; 
#define __obfs_0a5c79b__ case 
#define __obfs_4aa0e93b91__ WINTERPEASHOOTER: 
#define __obfs_1aa057313c28fa4__ distance_cost 
#define __obfs_1b__ = 
#define __obfs_494b__ 2 
#define __obfs_6fec24eac__ - 
#define __obfs_d8ab1a52f058358b__ 0.1 
#define __obfs_fed__ * 
#define __obfs_f5496252609c43__ j; 
#define __obfs_bdb6920ad__ break; 
#define __obfs_bb073f2__ } 
#define __obfs_6917ff2a7__ score[i] 
#define __obfs_be767243ca8f57__ += 
#define __obfs_c8cd63e1bf13c501__ Plants[i][j] 
#define __obfs_639d79cc8__ * 
#define __obfs_a2186aa7c__ plants_score[i] 
#define __obfs_b6e710870acb__ * 
#define __obfs_663fd3c5144fd10__ distance_cost; 
#define __obfs_1091660f3dff__ } 
#define __obfs_f44ee263952e65__ } 
#define __obfs_a9986c__ double 
#define __obfs_ce60ff__ zombie_cost[5] 
#define __obfs_f14bc21be7eaee__ = 
#define __obfs_d3__ {2.0, 
#define __obfs_1706f191d760c7__ 10, 
#define __obfs_2bb0502c8__ 12, 
#define __obfs_a081cab429ff7a3b__ -4, 
#define __obfs_78bc62d08a9a0__ -6}; 
#define __obfs_dc6a7e__ int 
#define __obfs_ccd2e3e__ nearest_zombie_per_row[5]={0,0,0,0,0}; 
#define __obfs_748d6b6ed8e__ for 
#define __obfs_05b8caaf6__ (int 
#define __obfs_6a__ i 
#define __obfs_8004d637b6236__ = 
#define __obfs_512fc3c5__ 0; 
#define __obfs_4db0f8b0fc8__ i 
#define __obfs_60792d855cd8a9__ < 
#define __obfs_3b502__ ROW; 
#define __obfs_ada5e0b63ef60e22__ i++) 
#define __obfs_b23f5220__ { 
#define __obfs_cc3d69ed781b16__ for 
#define __obfs_62f91ce9b82__ (int 
#define __obfs_c5d9256689c4__ j 
#define __obfs_96629f1aac6d__ = 
#define __obfs_75b9b6dc7fe444__ COLUMN-1; 
#define __obfs_37e7897__ j 
#define __obfs_4aec1b3__ >=0; 
#define __obfs_1cfead9959__ j--) 
#define __obfs_ffbd6c__ { 
#define __obfs_d4a897919a124958__ int 
#define __obfs_e9f__ k 
#define __obfs_9e6a921fbc42__ = 
#define __obfs_87f4d79__ 0; 
#define __obfs_532b7cbe070a357__ while 
#define __obfs_bbb001ba009ed117__ (Zombies[i][j][k] 
#define __obfs_366f0bc7bd1d__ != 
#define __obfs_58191d__ -1) 
#define __obfs_8b___ { 
#define __obfs_f0031__ double 
#define __obfs_f42c7f9c8aea__ distance_cost=1; 
#define __obfs_f231f2107df__ switch(Zombies[i][j][k]){ 
#define __obfs_097e26b2__ case 
#define __obfs_a2d__ NORMAL: 
#define __obfs_2e0a__ distance_cost=1.2-0.02*(j); 
#define __obfs_7c78335a8924215__ break; 
#define __obfs_019f8b946__ case 
#define __obfs_9f8684__ POLEVAULT: 
#define __obfs_ca1d3153a1c__ distance_cost=1.1-0.01*j; 
#define __obfs_dff8e9c2a__ break; 
#define __obfs_c6a01432c8138d__ case 
#define __obfs_c922de9e__ BUCKET: 
#define __obfs_54fd__ distance_cost=1.3-0.04*j; 
#define __obfs_fb26__ break; 
#define __obfs_7221e5c8e__ } 
#define __obfs_35937e3__ score[i] 
#define __obfs_8b83881__ += 
#define __obfs_2ecd2bd94734e5d__ zombie_cost[(Zombies[i][j][k] 
#define __obfs_8c9a__ - 
#define __obfs_86b20716fbd5b253__ 1)]*distance_cost; 
#define __obfs_e8bf0f27d70__ k++; 
#define __obfs_747d344__ nearest_zombie_per_row[i]=j; 
#define __obfs_92a08bf91__ } 
#define __obfs_bd8528251__ } 
#define __obfs_0afa92fc0f8a9cf0__ } 
#define __obfs_a41b3bb3e6b05__ int 
#define __obfs_1160453__ *serial_num 
#define __obfs_5d4__ = 
#define __obfs_38ed16__ rank(score, 
#define __obfs_d8___ ROW); 
#define __obfs_32b3ee0272954__ for 
#define __obfs_77ee3bc__ (int 
#define __obfs_98____ i 
#define __obfs_32cbf687880eb1__ = 
#define __obfs_9a____ 0; 
#define __obfs_fdbd31f2027f2__ i 
#define __obfs_b22b257ad05__ < 
#define __obfs_2227d75__ ROW; 
#define __obfs_2b45e8d6abf590__ i++) 
#define __obfs_55d99a37b2e__ { 
#define __obfs_99ef04e__ int 
#define __obfs_9808ae__ j 
#define __obfs_29539ed932d3__ = 
#define __obfs_d6___ 0; 
#define __obfs_6a4d5952d4c__ while 
#define __obfs_98b17f068d__ (Plants[serial_num[0]][j] 
#define __obfs_b299ad86__ == 
#define __obfs_5e6d27a7a8a8330d__ NOPLANT) 
#define __obfs_20c86a628232a67__ { 
#define __obfs_ce393994e8cf4308__ j++; 
#define __obfs_7a98af17e__ } 
#define __obfs_73e5080f0f3804__ player->PlacePlant(SUNFLOWER, 
#define __obfs_976abf__ serial_num[0], 
#define __obfs_e25cfa90f043__ nearest_zombie_per_row[serial_num[i]]-1); 
#define __obfs_e8258e5140317__ } 
#define __obfs_45c__ } 
#define __obfs_ce47be4abd__ } 
#define __obfs_59dfa2df42d9e3d__ void 
#define __obfs_d3630410c51e60__ value() 
#define __obfs_ba95d78a7c9425__ { 
#define __obfs_91378b__ this->value_peashooter(); 
#define __obfs_c20a7ce2a627ba__ this->value_sunflower(); 
#define __obfs_f4aa__ this->value_smallmnut(); 
#define __obfs_8051a3c405__ } 
#define __obfs_d98961__ void 
#define __obfs_3eb414bf1c2a66a__ make_decision() 
#define __obfs_39ae2e__ { 
#define __obfs_3f4__ this->beginning_operation(); 
#define __obfs_31c0__ this->GameState_2_50(); 
#define __obfs_8d30aa96__ this->GameState_50_200(); 
#define __obfs_8832ae391__ this->value(); 
#define __obfs_07c4b1fdd1ef8d__ } 
#define __obfs_f023559c6d59c0__ }; 
#define __obfs_766e428d1e23__ class 
#define __obfs_68a9__ value_zombie_func 
#define __obfs_563ca5e068b__ { 
#define __obfs_7f01c939761597__ public: 
#define __obfs_6c4bb__ int 
#define __obfs_721e7285__ nozombie; 
#define __obfs_b08354f36__ int 
#define __obfs_b59307fdacf7__ normal_choice; 
#define __obfs_731ae30af8750c2__ int 
#define __obfs_24ec8468b67314c2__ bucket_choice; 
#define __obfs_74___ int 
#define __obfs_799de6d3dae4c__ polevault_choice; 
#define __obfs_640258597__ int 
#define __obfs_9ef2ed4b7fd2c__ sled_choice; 
#define __obfs_211ed78fe__ int 
#define __obfs_d77e68596c__ gargantuar_choice; 
#define __obfs_2ef248c04979__ double 
#define __obfs_12___ value[ZOMBIE_KIND]; 
#define __obfs_731309c4bb__ int 
#define __obfs_6b620__ choice[ZOMBIE_KIND] 
#define __obfs_0aae0f__ = 
#define __obfs_9bd5ee6fe__ {this->normal_choice, 
#define __obfs_89d4402dc03d3__ this->bucket_choice, 
#define __obfs_e2ea__ this->polevault_choice, 
#define __obfs_133b37__ this->sled_choice, 
#define __obfs_52edc__ this->gargantuar_choice}; 
#define __obfs_b016935__ int 
#define __obfs_94b5bde6de888ddf__ BrokenLinesScore; 
#define __obfs_5812f92450cc__ int 
#define __obfs_f5___ KillPlantsScore; 
#define __obfs_687__ int 
#define __obfs_df8397__ LeftPlants; 
#define __obfs_0d352b4__ int 
#define __obfs_6dfe08eda7__ Score; 
#define __obfs_907edb0aa698622__ int 
#define __obfs_aac61539fd1fb__ time; 
#define __obfs_040a99f2__ int 
#define __obfs_85ae750ad1__ *PlaceCD; 
#define __obfs_c12706a__ int 
#define __obfs_c3d377d10b13__ **Plants; 
#define __obfs_12e0860668__ int 
#define __obfs_b6d67__ ***Zombies; 
#define __obfs_c5___ int 
#define __obfs_f87522788a2be2d__ *LeftLines; 
#define __obfs_ddcb155__ int 
#define __obfs_544a__ Sun; 
#define __obfs_528aecdf9cf__ int 
#define __obfs_ae35__ zombie_nums; 
#define __obfs_d15426b9c324676__ Game 
#define __obfs_a64bd53139f71961__ game; 
#define __obfs_032__ value_zombie_func(int 
#define __obfs_38811c5285__ BrokenLinesScore, 
#define __obfs_88e1__ int 
#define __obfs_0e1e__ KillPlantsScore, 
#define __obfs_d309cd6__ int 
#define __obfs_ac4508__ Score, 
#define __obfs_c57abe86de__ int 
#define __obfs_06132__ time, 
#define __obfs_326fb04c3abf030__ int 
#define __obfs_504c__ *PlaceCD, 
#define __obfs_1e3b21cb__ int 
#define __obfs_4ad13f04ef4373__ **Plants, 
#define __obfs_8deb8d1dd__ int 
#define __obfs_2067e2650cd701__ ***Zombies, 
#define __obfs_2131__ int 
#define __obfs_4ea83d951990d8__ *LeftLines, 
#define __obfs_485__ int 
#define __obfs_a87d2__ Sun, 
#define __obfs_d54ce9de9df77c__ int 
#define __obfs_951__ zombie_nums, 
#define __obfs_8a50bae297__ Game 
#define __obfs_f8037f94e53__ game) 
#define __obfs_f0eaf5__ { 
#define __obfs_f4334c131c781e2__ this->normal_choice 
#define __obfs_ac730__ = 
#define __obfs_073b0__ this->bucket_choice 
#define __obfs_a4d92e2cd5__ = 
#define __obfs_c91e34__ this->polevault_choice 
#define __obfs_3f__ = 
#define __obfs_bfbb56bee68d99af__ this->sled_choice 
#define __obfs_79514e888b8f2ac__ = 
#define __obfs_9c8661befa__ this->gargantuar_choice 
#define __obfs_2b323d6__ = 
#define __obfs_52b738__ 0; 
#define __obfs_b5___ this->BrokenLinesScore 
#define __obfs_fd8c0__ = 
#define __obfs_f507783927f2e__ BrokenLinesScore; 
#define __obfs_70___ this->KillPlantsScore 
#define __obfs_cc9657884708170__ = 
#define __obfs_60a70bb05b08d6__ KillPlantsScore; 
#define __obfs_a495e__ this->Score 
#define __obfs_c819904dde__ = 
#define __obfs_c1d0f19c3f__ Score; 
#define __obfs_72b386224056b__ this->time 
#define __obfs_9ddb__ = 
#define __obfs_946e3ece1fc8__ time; 
#define __obfs_b98249b38337c508__ this->PlaceCD 
#define __obfs_645e6bfdd05d1__ = 
#define __obfs_3a3__ PlaceCD; 
#define __obfs_980a875f__ this->Plants 
#define __obfs_cfcce0621b49c98__ = 
#define __obfs_ca3ec598__ Plants; 
#define __obfs_7a4303__ this->Zombies 
#define __obfs_d5d7f5bb__ = 
#define __obfs_42cd6__ Zombies; 
#define __obfs_7a4bf9ba2b__ this->LeftLines 
#define __obfs_fa84632d7__ = 
#define __obfs_737__ LeftLines; 
#define __obfs_63bfd6e8f26d1d3__ this->Sun 
#define __obfs_8217bb4e7fa054__ = 
#define __obfs_6fab6e3aa__ Sun; 
#define __obfs_f2____ this->zombie_nums 
#define __obfs_0e9d935f7e__ = 
#define __obfs_b84__ zombie_nums; 
#define __obfs_16fc18d7__ this->game 
#define __obfs_d7aab42e6b8__ = 
#define __obfs_c4b43ae017__ game; 
#define __obfs_2b7b82a7ec6de40__ for 
#define __obfs_69386f6bb1d__ (int 
#define __obfs_bdd8817990ef209f__ i 
#define __obfs_334467d41d5cf2__ = 
#define __obfs_09___ 0; 
#define __obfs_c46482d__ i 
#define __obfs_62dad6e273d322__ < 
#define __obfs_8ce5d989374d2__ ZOMBIE_KIND; 
#define __obfs_2c758__ i++) 
#define __obfs_831b1ac5__ this->value[i] 
#define __obfs_8a1d694707__ = 
#define __obfs_36ed197b3f31__ 0; 
#define __obfs_3cfbdf46__ memset(this->choice, 
#define __obfs_f7cfdde9db36af8__ 0, 
#define __obfs_a435__ ZOMBIE_KIND 
#define __obfs_3ce6d3c__ * 
#define __obfs_93682__ (sizeof(int))); 
#define __obfs_dba132f6a__ } 
#define __obfs_20b02dc951715__ int 
#define __obfs_e94fe9a__ judge_whether_big_cost_in_one_row(int 
#define __obfs_ac8cd1808__ *cost) 
#define __obfs_29969626__ { 
#define __obfs_0a2a51dac613882__ double 
#define __obfs_b0ab42fcb71331__ average 
#define __obfs_2be9bd__ = 
#define __obfs_331316d4efb44__ 0, 
#define __obfs_59a__ square_distance 
#define __obfs_98bd65207ee83bf__ = 
#define __obfs_a4fa7175d4__ 0; 
#define __obfs_2de7cf2__ for 
#define __obfs_7ba06__ (int 
#define __obfs_f47122__ i 
#define __obfs_acf06cdd9c74__ = 
#define __obfs_14491b756__ 0; 
#define __obfs_21c__ i 
#define __obfs_3083__ < 
#define __obfs_38a77aa456f__ ROW; 
#define __obfs_0655__ i++) 
#define __obfs_1a04f96__ { 
#define __obfs_333cb763f__ average 
#define __obfs_69f268fb2ba__ += 
#define __obfs_b7ee0d0d4__ cost[i]; 
#define __obfs_0b6ace9e897__ } 
#define __obfs_0987b8b33__ average 
#define __obfs_8b9e7ab295e8__ /= 
#define __obfs_d2cd33e9__ 5; 
#define __obfs_ca793d8b79c1b66__ for 
#define __obfs_a36b__ (int 
#define __obfs_0cd6a652__ i 
#define __obfs_97108695bd93b6b__ = 
#define __obfs_82b0639a82d0cc7__ 0; 
#define __obfs_75df63609809c__ i 
#define __obfs_8d9766a__ < 
#define __obfs_39cd7b469beae7__ ROW; 
#define __obfs_664dd8__ i++) 
#define __obfs_8a1ee9f2__ { 
#define __obfs_b445e3141__ square_distance 
#define __obfs_07f75d9144912__ += 
#define __obfs_0e7e05__ (cost[i] 
#define __obfs_165a59f7cf3b5c__ - 
#define __obfs_dda99de58__ average) 
#define __obfs_900c563bfd2c48__ * 
#define __obfs_285da2198b2b496c__ (cost[i] 
#define __obfs_37d0b499__ - 
#define __obfs_0084ae4b__ average); 
#define __obfs_6c349__ } 
#define __obfs_9b9b05072dd20d1__ square_distance 
#define __obfs_14___ = 
#define __obfs_a9b4__ pow(square_distance, 
#define __obfs_2e___ 0.5); 
#define __obfs_88855547570f7__ square_distance 
#define __obfs_f2bff080785c__ /= 
#define __obfs_6e16656a6ee1de72__ 5; 
#define __obfs_29ddbd__ if 
#define __obfs_0668e20b__ (square_distance 
#define __obfs_2517756c5__ > 
#define __obfs_131f383b43__ pow(this->time, 
#define __obfs_31ca0ca71184bbd__ 0.01) 
#define __obfs_4a11__ * 
#define __obfs_62___ 100) 
#define __obfs_8643c__ { 
#define __obfs_8ed36a84__ return 
#define __obfs_dbb422937d7f__ 1; 
#define __obfs_6463c88460bd63bb__ } 
#define __obfs_477b0__ else 
#define __obfs_e8a642ed__ return 
#define __obfs_82875__ 0; 
#define __obfs_818de4d2ec21__ } 
#define __obfs_5c80985bd40b8c__ void 
#define __obfs_384babc3e7__ make_decision(int 
#define __obfs_57f04bb2975420__ *decision) 
#define __obfs_e945de21a1bb57__ { 
#define __obfs_7fcc__ int 
#define __obfs_91d0dbfd3__ *cost 
#define __obfs_898dd88c__ = 
#define __obfs_c6b8c8d762da__ this->game.zombieCostPerRow; 
#define __obfs_be1bc79__ if 
#define __obfs_32fdab6559cdfa4__ (judge_whether_big_cost_in_one_row(cost) 
#define __obfs_dab49080d80c7__ == 
#define __obfs_73__ 0) 
#define __obfs_20125fd__ { 
#define __obfs_c6f798b__ double 
#define __obfs_2fd0fd3efa7c4cf__ max 
#define __obfs_90f1__ = 
#define __obfs_30__ value[0]; 
#define __obfs_63a7769efb__ for 
#define __obfs_f6d9e4__ (int 
#define __obfs_1f___ i 
#define __obfs_471c50ad1a1__ = 
#define __obfs_d594b1a__ 0; 
#define __obfs_4a53__ i 
#define __obfs_643de__ < 
#define __obfs_e846fb8a__ 5; 
#define __obfs_73640de25b7__ i++) 
#define __obfs_3d324c288__ { 
#define __obfs_71a5c0514ab83__ if 
#define __obfs_072__ (max 
#define __obfs_5d2c2cee__ < 
#define __obfs_5421e013565f7f1__ this->value[i]) 
#define __obfs_4500e4037738__ { 
#define __obfs_caa__ max 
#define __obfs_2d2c8394e31101a2__ = 
#define __obfs_84c2d4860a0fc2__ this->value[i]; 
#define __obfs_7200798__ decision[0] 
#define __obfs_a91af177d301__ = 
#define __obfs_14c879f3f5d__ i 
#define __obfs_5b970a1d9b__ + 
#define __obfs_61f2585b__ 1; 
#define __obfs_c2f__ decision[1] 
#define __obfs_f34185c4ca5d58e__ = 
#define __obfs_4fa91c19016__ this->choice[i]; 
#define __obfs_7de3__ } 
#define __obfs_b2004314__ } 
#define __obfs_586f9b4035e599__ } 
#define __obfs_12092__ else 
#define __obfs_758be1f9f7__ { 
#define __obfs_09ba3f0df1__ double 
#define __obfs_5b4a214624__ min 
#define __obfs_2e1b24__ = 
#define __obfs_c5____ value[0]; 
#define __obfs_86a1793__ for 
#define __obfs_703__ (int 
#define __obfs_de7f47e09c8e05e6__ i 
#define __obfs_66121d1f782d__ = 
#define __obfs_f356355c163483__ 0; 
#define __obfs_5abdf8b852__ i 
#define __obfs_473447ac58e1__ < 
#define __obfs_def7924e3199be5e__ 5; 
#define __obfs_e1_____ i++) 
#define __obfs_e3ea33961a7c__ { 
#define __obfs_13d63838ef1fb__ if 
#define __obfs_56503192b141__ (min 
#define __obfs_7e8d7e5__ > 
#define __obfs_9edda0fd__ this->value[i]) 
#define __obfs_73c0318__ { 
#define __obfs_51e6__ min 
#define __obfs_797134c3e4__ = 
#define __obfs_606555__ this->value[i]; 
#define __obfs_2a2717956118b__ decision[0] 
#define __obfs_322f62469c5e__ = 
#define __obfs_ca851e9f71b25d2__ i 
#define __obfs_73fed7fd472e502d__ + 
#define __obfs_735143e9__ 1; 
#define __obfs_2974788b53f73e__ decision[1] 
#define __obfs_99be__ = 
#define __obfs_e91068fff3d7__ this->choice[i]; 
#define __obfs_d38ee1__ } 
#define __obfs_dd___ } 
#define __obfs_6d6968d87__ if 
#define __obfs_b071c__ (this->zombie_nums 
#define __obfs_6950aa0__ > 
#define __obfs_e8e0d__ (this->time 
#define __obfs_3fb049__ / 
#define __obfs_b7fe__ 100 
#define __obfs_cb953f6__ + 
#define __obfs_966b6dfb__ 4)) 
#define __obfs_dfeb9598fbfb97__ { 
#define __obfs_ab4f__ decision[0] 
#define __obfs_944a5ae3483ed5c__ = 
#define __obfs_c7b90b0fc2372__ decision[1] 
#define __obfs_1b318124e37af6d__ = 
#define __obfs_72f67e70f6b7cd__ NOZOMBIE; 
#define __obfs_6c91724b8__ } 
#define __obfs_0060e__ } 
#define __obfs_ba036d228858d76f__ } 
#define __obfs_6dbd2699e8e__ bool 
#define __obfs_84_____ whether_need_compute(int 
#define __obfs_0a3__ kind) 
#define __obfs_7535bbb91c8__ { 
#define __obfs_fd9dcf1d14__ if 
#define __obfs_3ea2db50e6__ (this->PlaceCD[kind 
#define __obfs_e2065cb56f55334__ - 
#define __obfs_d4___ 1] 
#define __obfs_d2350a54__ > 
#define __obfs_87f__ 0) 
#define __obfs_73231e__ { 
#define __obfs_2a3d6__ this->choice[kind 
#define __obfs_e0126439e08ddfbd__ - 
#define __obfs_0e7__ 1] 
#define __obfs_7d2be41b1bd__ = 
#define __obfs_0141a8aedb1b53__ 0; 
#define __obfs_15e122__ this->value[kind 
#define __obfs_9a85c12a21b7639__ - 
#define __obfs_0dbb3fb9a__ 1] 
#define __obfs_0f___ = 
#define __obfs_7288251__ -100000; 
#define __obfs_5fef3e__ return 
#define __obfs_cf1cf43cba274ae__ true; 
#define __obfs_b5b0db7f3a77ca4__ } 
#define __obfs_5401acfe__ else 
#define __obfs_1fd7b8__ return 
#define __obfs_6c0958d82a83__ false; 
#define __obfs_98afdcc1ebd85da__ } 
#define __obfs_ee14c41e92ec5c9__ double 
#define __obfs_93931410__ zombie_cost(int 
#define __obfs_a9de093d__ row, 
#define __obfs_da9e6a4a4aeca9__ double 
#define __obfs_0e4f5c__ *zombies_paras, 
#define __obfs_b87470__ double 
#define __obfs_ead81fe8__ distance_cost, 
#define __obfs_9bdb8b1faffa4b__ double 
#define __obfs_30a0b736094__ distance_rate, 
#define __obfs_e52ad5c9__ int 
#define __obfs_afab3e97074__ kind) 
#define __obfs_5a9d8bf5b7a4b35f__ { 
#define __obfs_aa97d584861474f__ double 
#define __obfs_b99d193b66a65429__ cost 
#define __obfs_291d43c696d8c370__ = 
#define __obfs_416849da96fb7__ 0.0; 
#define __obfs_1458e7509aa5f4__ if 
#define __obfs_142c65e00f4f7cf__ (this->LeftLines[row] 
#define __obfs_8844c5f0037__ == 
#define __obfs_c5f5c23be__ 0) 
#define __obfs_8487__ { 
#define __obfs_196__ cost 
#define __obfs_147ebe637038ca5__ = 
#define __obfs_06____ -100000; 
#define __obfs_a8166__ } 
#define __obfs_e6ba70fc093b4c__ else 
#define __obfs_50____ { 
#define __obfs_db98dc0dbafde48__ int 
#define __obfs_01__ num_per_row 
#define __obfs_ab__ = 
#define __obfs_7c220__ 0; 
#define __obfs_e250c59336b505e__ double 
#define __obfs_69b09198d4248__ too_many_zombies_cost 
#define __obfs_22b1cd16__ = 
#define __obfs_656f0__ -1.5; 
#define __obfs_51da85a3c3dfa1f__ for 
#define __obfs_285a25__ (int 
#define __obfs_f11bec1411101c7__ j 
#define __obfs_0ae1dd3__ = 
#define __obfs_414a74971__ 0; 
#define __obfs_ebf1__ j 
#define __obfs_d04d42cdf14579__ < 
#define __obfs_05edf455__ COLUMN; 
#define __obfs_e6e713296__ j++) 
#define __obfs_6346dc72__ { 
#define __obfs_dccab9bd9e__ int 
#define __obfs_5481b2f__ k 
#define __obfs_77c493ec14246__ = 
#define __obfs_43b52842663fa6__ 0; 
#define __obfs_f8f5161cf94d__ while 
#define __obfs_842424a1d__ (this->Zombies[row][j][k] 
#define __obfs_8baca01b73__ != 
#define __obfs_1b9f__ -1) 
#define __obfs_c9f06bc__ { 
#define __obfs_3f647__ switch 
#define __obfs_3e77a146297754__ (kind) 
#define __obfs_25___ { 
#define __obfs_0d441de75945e5__ case 
#define __obfs_630b7d8dd__ POLEVAULT: 
#define __obfs_6760__ cost 
#define __obfs_9d684c589d67031__ += 
#define __obfs_69eba3__ zombies_paras[this->Zombies[row][j][k] 
#define __obfs_565767eb96d87__ - 
#define __obfs_2668a710__ 1] 
#define __obfs_224e5__ * 
#define __obfs_aba53da__ ((COLUMN 
#define __obfs_c2964caac096f__ - 
#define __obfs_a38__ j 
#define __obfs_da6ea7747__ - 
#define __obfs_9001ca429212011__ distance_cost) 
#define __obfs_69f357fcc8e6d__ * 
#define __obfs_cdd0__ (COLUMN 
#define __obfs_dce8af__ - 
#define __obfs_c0____ j 
#define __obfs_52c409f1571f5__ - 
#define __obfs_b89c30965eb__ distance_cost)); 
#define __obfs_6a450490f238b4d__ break; 
#define __obfs_e7e69cdf28f8c__ default: 
#define __obfs_8d762__ cost 
#define __obfs_62e7f2e__ += 
#define __obfs_228b25587479f__ zombies_paras[this->Zombies[row][j][k] 
#define __obfs_6a8018b__ - 
#define __obfs_c254e7753095807e__ 1] 
#define __obfs_a05d8861__ * 
#define __obfs_774b0e0775__ (-distance_rate 
#define __obfs_967990de5b3ea__ * 
#define __obfs_60a0575__ (COLUMN 
#define __obfs_649a0__ - 
#define __obfs_f95ec__ j 
#define __obfs_4c__ - 
#define __obfs_d87ca511e2a8593c__ distance_cost) 
#define __obfs_c4fa7aeceda__ * 
#define __obfs_6ad__ (COLUMN 
#define __obfs_d8c9d05ec6e__ - 
#define __obfs_78d__ j 
#define __obfs_db___ - 
#define __obfs_4da9d7__ distance_cost) 
#define __obfs_820e694038__ + 
#define __obfs_4baf54f36935058__ 2); 
#define __obfs_c5b2__ } 
#define __obfs_856b5__ k++; 
#define __obfs_ecdcd675b3__ num_per_row++; 
#define __obfs_5ee0070c4__ } 
#define __obfs_dd7970532bfa__ } 
#define __obfs_0ee8b85a85a49346__ cost 
#define __obfs_2bf283c0__ += 
#define __obfs_3e524bf740__ num_per_row 
#define __obfs_1305f6__ * 
#define __obfs_1a551829d50f1400__ too_many_zombies_cost; 
#define __obfs_fd4c2dc64ccb849__ } 
#define __obfs_398475c83b47075e__ return 
#define __obfs_acf9221__ cost; 
#define __obfs_e2ea___ } 
#define __obfs_a098b2eb313__ int 
#define __obfs_48042b1dae4__ **sum_plants_per_row() 
#define __obfs_cae82d435__ { 
#define __obfs_895daa408f494a__ int 
#define __obfs_ba304f3809ed__ **plants_num_format 
#define __obfs_4f11b55f__ = 
#define __obfs_22c5a901070d1__ (int 
#define __obfs_300d15__ **)malloc(ROW 
#define __obfs_7ae11af20__ * 
#define __obfs_8a05726__ sizeof(int 
#define __obfs_d0aa51__ *)); 
#define __obfs_b5a1d925221__ for 
#define __obfs_0d8080853a54__ (int 
#define __obfs_cff02a74da64__ i 
#define __obfs_49c0__ = 
#define __obfs_45ce__ 0; 
#define __obfs_c203e__ i 
#define __obfs_e1021d43911ca2c__ < 
#define __obfs_2da6cc4a5d__ ROW; 
#define __obfs_cf88118aa2ba__ i++) 
#define __obfs_310cc7ca5a76a446__ { 
#define __obfs_14678db82874f1__ plants_num_format[i] 
#define __obfs_a22d33b4a00c__ = 
#define __obfs_30a237d18c50f563__ (int 
#define __obfs_0784__ *)malloc(sizeof(int) 
#define __obfs_9627c45df__ * 
#define __obfs_e761813f83dfc86f__ PLANT_KIND); 
#define __obfs_2b346a0aa__ memset(plants_num_format[i], 
#define __obfs_ddf9029977a612__ 0, 
#define __obfs_b67fb3360__ PLANT_KIND 
#define __obfs_6915849303a3fe9__ * 
#define __obfs_1ea97de85eb__ sizeof(int)); 
#define __obfs_f095cedd__ } 
#define __obfs_1d2a48c55f6f1__ for 
#define __obfs_e1______ (int 
#define __obfs_77ec6f21c85b637__ i 
#define __obfs_54__ = 
#define __obfs_f3c89__ 0; 
#define __obfs_740a02d__ i 
#define __obfs_f35__ < 
#define __obfs_845__ ROW; 
#define __obfs_113383__ i++) 
#define __obfs_71d7232b9fed02__ { 
#define __obfs_2151__ for 
#define __obfs_74791__ (int 
#define __obfs_212__ j 
#define __obfs_9426c311e76__ = 
#define __obfs_89__ 0; 
#define __obfs_acb5d11__ j 
#define __obfs_c90e2__ < 
#define __obfs_55__ COLUMN; 
#define __obfs_dc727151e5d55__ j++) 
#define __obfs_6754e06e46__ { 
#define __obfs_d880067__ switch 
#define __obfs_39ea40e164f9__ (this->Plants[i][j]) 
#define __obfs_781397bc0630__ { 
#define __obfs_8abfe8__ case 
#define __obfs_882735cbdfd9f81__ SUNFLOWER: 
#define __obfs_f23d125da1e29__ plants_num_format[i][SUNFLOWER 
#define __obfs_4b26dc4663c__ - 
#define __obfs_af1b57__ 1]++; 
#define __obfs_95c9d994f8d75d__ break; 
#define __obfs_0b105cf1504c4e__ case 
#define __obfs_943aa0fcda4ee2__ WINTERPEASHOOTER: 
#define __obfs_a18630a__ plants_num_format[i][WINTERPEASHOOTER 
#define __obfs_f92586a25__ - 
#define __obfs_b181eaa__ 1]++; 
#define __obfs_a928731e103dfc6__ break; 
#define __obfs_7d2__ case 
#define __obfs_9308b0d6e58__ PEASHOOTER: 
#define __obfs_2cfa3753d6a__ plants_num_format[i][PEASHOOTER 
#define __obfs_4764f37856fc727f__ - 
#define __obfs_2ad__ 1]++; 
#define __obfs_34ffeb359a192eb8__ break; 
#define __obfs_56db57b4db__ case 
#define __obfs_55057122__ SMALLNUT: 
#define __obfs_aba__ plants_num_format[i][SMALLNUT 
#define __obfs_87ae6f__ - 
#define __obfs_7553e94d39fd46__ 1]++; 
#define __obfs_e36286b9__ break; 
#define __obfs_d2d2c6e2__ case 
#define __obfs_1b32__ PEPPER: 
#define __obfs_240c945b__ plants_num_format[i][PEPPER 
#define __obfs_9d068c869fd3e__ - 
#define __obfs_9e740__ 1]++; 
#define __obfs_532b81fa__ break; 
#define __obfs_9e4__ case 
#define __obfs_56e6a9__ SQUASH: 
#define __obfs_afa299a__ plants_num_format[i][SQUASH 
#define __obfs_4172f3101212a2__ - 
#define __obfs_94ef7214__ 1]++; 
#define __obfs_9fe77ac7__ break; 
#define __obfs_d3802b1d__ } 
#define __obfs_460b491b9__ } 
#define __obfs_cb16b8498f7__ } 
#define __obfs_d8c2__ return 
#define __obfs_7ec3b3c__ plants_num_format; 
#define __obfs_ee23e7ad9b__ } 
#define __obfs_64d52e08cc03e60__ double 
#define __obfs_9d752cb08ef466fc__ plant_cost(int 
#define __obfs_dc0c3__ row, 
#define __obfs_3e195__ int 
#define __obfs_3db11d259a9db7f__ **plants_num_format, 
#define __obfs_167__ double 
#define __obfs_208__ *plants_para, 
#define __obfs_33____ int 
#define __obfs_63ce12dcf1ede__ kind) 
#define __obfs_1f72e258f__ { 
#define __obfs_09____ double 
#define __obfs_56517f19__ cost 
#define __obfs_6d3a2d2__ = 
#define __obfs_e8542a04d734d__ 0.0; 
#define __obfs_d884__ switch 
#define __obfs_aaac__ (kind) 
#define __obfs_f9beb1e__ { 
#define __obfs_685__ case 
#define __obfs_21ce68__ NORMAL: 
#define __obfs_48d__ if 
#define __obfs_258e1304762902__ (plants_num_format[row][SMALLNUT 
#define __obfs_2e3d2c4f3__ - 
#define __obfs_cd3bbc2d7ca1__ 1] 
#define __obfs_91f9fec9__ > 
#define __obfs_b4affa4f6b27df04__ 0 
#define __obfs_3df0__ && 
#define __obfs_cbf__ plants_num_format[row][PEASHOOTER 
#define __obfs_27e8e17134dd__ - 
#define __obfs_092cb13c22d5__ 1] 
#define __obfs_9332c513ef44b__ + 
#define __obfs_7ba6d33c__ plants_num_format[row][WINTERPEASHOOTER 
#define __obfs_641d77dd5271f__ - 
#define __obfs_211a7a84d3d5c__ 1] 
#define __obfs_79cae1be0__ > 
#define __obfs_d74cb35__ 0) 
#define __obfs_28d437661d__ plants_para[SMALLNUT 
#define __obfs_4625d8e31dad7d1c__ - 
#define __obfs_7f6___ 1] 
#define __obfs_20___ *= 
#define __obfs_83ddfb__ (plants_num_format[row][PEASHOOTER 
#define __obfs_5c15__ - 
#define __obfs_73f104c9fba50050__ 1] 
#define __obfs_f2_____ * 
#define __obfs_2119b8d43e__ 1 
#define __obfs_ad___ + 
#define __obfs_cab070d53__ plants_num_format[row][WINTERPEASHOOTER 
#define __obfs_8ce87b__ - 
#define __obfs_3569df15__ 1] 
#define __obfs_9fc664__ * 
#define __obfs_f87e955fd6b89f89__ 2); 
#define __obfs_1aa___ break; 
#define __obfs_e16e74a6356__ case 
#define __obfs_44f__ BUCKET: 
#define __obfs_3430__ if 
#define __obfs_f31752__ (plants_num_format[row][SMALLNUT 
#define __obfs_deb74a85a4a6__ - 
#define __obfs_335d__ 1] 
#define __obfs_e73fecc08__ > 
#define __obfs_690bb3__ 0 
#define __obfs_4ecb679f__ && 
#define __obfs_c157297d1a1ff04__ plants_num_format[row][WINTERPEASHOOTER 
#define __obfs_916d3891a243c__ - 
#define __obfs_42547f5a4__ 1] 
#define __obfs_41c542dfe6e4f__ > 
#define __obfs_360__ 0) 
#define __obfs_c82836ed448c41__ plants_para[SMALLNUT 
#define __obfs_58___ - 
#define __obfs_63c6598__ 1] 
#define __obfs_9532__ *= 
#define __obfs_d3614f__ (plants_num_format[row][PEASHOOTER 
#define __obfs_e97__ - 
#define __obfs_37968ad196a5085__ 1] 
#define __obfs_98cac9d33aad44__ * 
#define __obfs_5e7__ 0.2 
#define __obfs_43a115cbd6f4788__ + 
#define __obfs_cd8d5260c813__ plants_num_format[row][WINTERPEASHOOTER 
#define __obfs_38ef4b66__ - 
#define __obfs_02ae6a786b__ 1]); 
#define __obfs_8068fee5f49946__ break; 
#define __obfs_40db__ case 
#define __obfs_0a49e3c3a03ebd__ POLEVAULT: 
#define __obfs_c563c2c394023a07__ if 
#define __obfs_143758ee65__ (plants_num_format[row][SMALLNUT 
#define __obfs_c911241__ - 
#define __obfs_fa6c94460e9__ 1] 
#define __obfs_b994697479c5716__ > 
#define __obfs_eb18482__ 0 
#define __obfs_91e5__ && 
#define __obfs_c04c1__ plants_num_format[row][PEASHOOTER 
#define __obfs_0e57098d03__ - 
#define __obfs_bca3__ 1] 
#define __obfs_67974233917ce__ + 
#define __obfs_c2___ plants_num_format[row][WINTERPEASHOOTER 
#define __obfs_a29__ - 
#define __obfs_b5b8c48482__ 1] 
#define __obfs_46d__ > 
#define __obfs_b7d0858d41a6c__ 0) 
#define __obfs_fcd__ { 
#define __obfs_cac8e1__ plants_para[SMALLNUT 
#define __obfs_ea9268cb__ - 
#define __obfs_65b1e92c585__ 1] 
#define __obfs_243be2818a23c9__ *= 
#define __obfs_1c66f4627f1b9679__ ((1.5 
#define __obfs_6e2eec9__ - 
#define __obfs_a6ade5aa93__ plants_num_format[row][SMALLNUT 
#define __obfs_f26df67__ - 
#define __obfs_9b2f00f37307f2c2__ 1]) 
#define __obfs_dfa037a53e1__ * 
#define __obfs_7da18d0326a9f__ (3 
#define __obfs_7fa215c9__ - 
#define __obfs_9eac1__ plants_num_format[row][PEASHOOTER 
#define __obfs_494__ - 
#define __obfs_c6d6445d97e__ 1] 
#define __obfs_6236c__ + 
#define __obfs_a30__ plants_num_format[row][WINTERPEASHOOTER 
#define __obfs_42c8938e4cf__ - 
#define __obfs_4f5a97__ 1])); 
#define __obfs_f550e0ba9e1c4e8b__ } 
#define __obfs_dc0__ case 
#define __obfs_582967e09__ SLED: 
#define __obfs_b9f35816__ if 
#define __obfs_31__ (plants_num_format[row][SMALLNUT 
#define __obfs_d58f855f__ - 
#define __obfs_4c2e5eaae91__ 1] 
#define __obfs_f269__ > 
#define __obfs_50dd7100__ 1 
#define __obfs_7171e95__ && 
#define __obfs_5a5eab21ca2a__ plants_num_format[row][PEASHOOTER 
#define __obfs_a61__ - 
#define __obfs_533fa79__ 1] 
#define __obfs_c4d2ce3f3ebb5__ + 
#define __obfs_4f8bc5ac1dc2b4__ plants_num_format[row][WINTERPEASHOOTER 
#define __obfs_866d90e0921__ - 
#define __obfs_a9df2255ad642b__ 1] 
#define __obfs_8e5__ > 
#define __obfs_70____ 0) 
#define __obfs_2c62__ { 
#define __obfs_c25__ plants_para[SMALLNUT 
#define __obfs_551cb238f48950__ - 
#define __obfs_d35b05a832e2bb9__ 1] 
#define __obfs_db346ccb62d4__ *= 
#define __obfs_2ed80f6311c182__ (plants_num_format[row][SMALLNUT 
#define __obfs_ccc81a9__ - 
#define __obfs_834a3bd235bc__ 1] 
#define __obfs_8d___ * 
#define __obfs_9854d7afce41__ plants_num_format[row][SMALLNUT 
#define __obfs_cc58f7abf0b0c__ - 
#define __obfs_0dd1bc__ 1]) 
#define __obfs_a1c5aff9__ * 
#define __obfs_df42e224__ (plants_num_format[row][WINTERPEASHOOTER 
#define __obfs_51f3eb940fd7__ - 
#define __obfs_8dcf2420e__ 1]); 
#define __obfs_31___ } 
#define __obfs_5db60c9820991__ break; 
#define __obfs_9649dec__ case 
#define __obfs_972__ GARGANTUAR: 
#define __obfs_8609__ if 
#define __obfs_cbfe568136__ (plants_num_format[row][WINTERPEASHOOTER 
#define __obfs_c2c__ - 
#define __obfs_fb0650__ 1] 
#define __obfs_e8d66338fab3727__ > 
#define __obfs_5c8e07__ 1) 
#define __obfs_ee188463935a061d__ { 
#define __obfs_4175f2ebb2__ plants_para[WINTERPEASHOOTER 
#define __obfs_b957__ - 
#define __obfs_37db6b__ 1] 
#define __obfs_fd___ *= 
#define __obfs_4837ba5cd49__ (plants_num_format[row][WINTERPEASHOOTER 
#define __obfs_4fc__ - 
#define __obfs_1517c8664be__ 1] 
#define __obfs_9d949c3d__ + 
#define __obfs_c09f9caf5e08836d__ 1); 
#define __obfs_63154d5661f__ } 
#define __obfs_e593__ } 
#define __obfs_3341f6f048384e__ plants_para[SUNFLOWER 
#define __obfs_576d02622__ - 
#define __obfs_4175a4b46a4__ 1] 
#define __obfs_1be883eec3231f__ *= 
#define __obfs_1bf50__ (1 
#define __obfs_27b587bbe83ae__ + 
#define __obfs_b085c4fa543a__ 1 
#define __obfs_b85d65c39e12__ / 
#define __obfs_39__ (COLUMN 
#define __obfs_49cbb759277__ - 
#define __obfs_4d9__ plants_num_format[row][SUNFLOWER 
#define __obfs_859b00aec8885efc__ - 
#define __obfs_5fc7c9bd1__ 1] 
#define __obfs_d6525aa8__ + 
#define __obfs_9b8f0779badba__ 1)); 
#define __obfs_d90e5b__ for 
#define __obfs_97f081d3b1__ (int 
#define __obfs_943b5fd1ef60d3a4__ j 
#define __obfs_1340ccf24722f__ = 
#define __obfs_4fc28b7093b135c__ 0; 
#define __obfs_d2__ j 
#define __obfs_1597d21403__ < 
#define __obfs_79f69230354b7120__ COLUMN; 
#define __obfs_679d8bbd776e__ j++) 
#define __obfs_acff1af62d0f91f4__ { 
#define __obfs_c56a022b1525052__ if 
#define __obfs_298__ (Plants[row][j] 
#define __obfs_f8f122d50eba11c3__ != 
#define __obfs_13e36f06c66134ad__ NOPLANT) 
#define __obfs_70fc5f04320__ cost 
#define __obfs_39486845643__ += 
#define __obfs_74c__ plants_para[Plants[row][j] 
#define __obfs_e5afb0f2dbc6d__ - 
#define __obfs_3f___ 1] 
#define __obfs_29e1c59be16__ * 
#define __obfs_ec36e2ba64f__ (plants_para[Plants[row][j] 
#define __obfs_da21ba__ - 
#define __obfs_f9fe8__ 1] 
#define __obfs_c3810d4a951__ > 
#define __obfs_71a__ 0 
#define __obfs_da4f21__ ? 
#define __obfs_6df182582740607__ (j 
#define __obfs_2e5c2cb8d13e8fba__ + 
#define __obfs_bb702465f3c314__ 1) 
#define __obfs_7f278ad602__ * 
#define __obfs_af8d__ (j 
#define __obfs_b928fec5932bf2f__ + 
#define __obfs_6e2d5d50a943a0e__ 1) 
#define __obfs_3f900db260__ : 
#define __obfs_0f3c5d0c3666eec8__ (COLUMN 
#define __obfs_86c51678350f656d__ - 
#define __obfs_bf5cd8__ j)); 
#define __obfs_806d92641__ } 
#define __obfs_ac52c6__ return 
#define __obfs_24e01830d21__ cost; 
#define __obfs_6f611188ad4__ } 
#define __obfs_f51238__ int 
#define __obfs_dd5__ max_index(double 
#define __obfs_db9ad56__ *a, 
#define __obfs_43d762__ int 
#define __obfs_b607ba5__ length) 
#define __obfs_0cbed40__ { 
#define __obfs_f81dee__ double 
#define __obfs_11bc__ max 
#define __obfs_cba0a4ee__ = 
#define __obfs_f2e84d__ -10000; 
#define __obfs_67800448__ int 
#define __obfs_9a32ff36c6__ index 
#define __obfs_4f5a9bf135f28535__ = 
#define __obfs_2ba3c4b9390__ 0; 
#define __obfs_7d571e5__ for 
#define __obfs_a8badd37c221a3__ (int 
#define __obfs_a58616464d142__ i 
#define __obfs_9425b__ = 
#define __obfs_1bda4__ 0; 
#define __obfs_a0443c8c8c33__ i 
#define __obfs_5e4450dc93010__ < 
#define __obfs_7059__ length; 
#define __obfs_0c2f66f437__ i++) 
#define __obfs_540393ae7f8b7a7__ { 
#define __obfs_4f9c76cf97f8__ if 
#define __obfs_bbbe7ef28a001__ (max 
#define __obfs_6516c__ < 
#define __obfs_7612936dcc8528__ a[i]) 
#define __obfs_dfbd282c18300fa0__ { 
#define __obfs_0de5__ max 
#define __obfs_c12d1f7cc7c4b41__ = 
#define __obfs_adf8d7f8c53c868__ a[i]; 
#define __obfs_d464b5ac9__ index 
#define __obfs_43e04__ = 
#define __obfs_abec16f483a__ i; 
#define __obfs_743__ } 
#define __obfs_9cf742e94f29f45__ } 
#define __obfs_1bd69c7__ return 
#define __obfs_ffc58105bf6__ index; 
#define __obfs_254ed__ } 
#define __obfs_3ce83f544dbe6__ void 
#define __obfs_f8eb27__ judge_Lines_not_broken(double 
#define __obfs_f23b3df__ *final_choice) 
#define __obfs_671__ { 
#define __obfs_ab8__ for 
#define __obfs_21b5680d__ (int 
#define __obfs_cb5f984421c__ i 
#define __obfs_6693a7a__ = 
#define __obfs_b14680de__ 0; 
#define __obfs_bd3ef5__ i 
#define __obfs_fbfe5ba2__ < 
#define __obfs_1cdf14d1e369__ ROW; 
#define __obfs_587524833eaf9__ i++) 
#define __obfs_f0___ { 
#define __obfs_621c090c3a61c__ if 
#define __obfs_45_____ (LeftLines[i] 
#define __obfs_7fc6__ == 
#define __obfs_1192265fb3__ 0) 
#define __obfs_aec851__ { 
#define __obfs_d5ff13537__ final_choice[i] 
#define __obfs_4e477793df9__ = 
#define __obfs_31____ -10000; 
#define __obfs_16__ } 
#define __obfs_c952ce__ } 
#define __obfs_ac4e7a4f341e7__ } 
#define __obfs_a09e75c5c86__ void 
#define __obfs_015e31933__ value_normal() 
#define __obfs_084a8a9a__ { 
#define __obfs_3be0__ double 
#define __obfs_3cc578f087e__ final_choice[ROW] 
#define __obfs_c0c78__ = 
#define __obfs_7f5fc754c7af0a__ {0, 
#define __obfs_4f81b1d964419__ 0, 
#define __obfs_5b5e__ 0, 
#define __obfs_d360a50__ 0, 
#define __obfs_56577889__ 0}; 
#define __obfs_1cd73be1e256a7__ judge_Lines_not_broken(final_choice); 
#define __obfs_ca4b3353__ if 
#define __obfs_da0b566359c__ (this->whether_need_compute(NORMAL)) 
#define __obfs_d3f5d4de09ea1946__ { 
#define __obfs_8fb134f258b1f786__ return; 
#define __obfs_df5354693__ } 
#define __obfs_ee0e95249268b8__ double 
#define __obfs_354ac345fd__ zombies_paras[ZOMBIE_KIND] 
#define __obfs_e366d105cfd__ = 
#define __obfs_5901fe__ {-5, 
#define __obfs_89a4779d3836__ 4, 
#define __obfs_38____ 2, 
#define __obfs_3e33b9__ 3, 
#define __obfs_90____ 1}; 
#define __obfs_9565f1cd832__ double 
#define __obfs_5487e79fa__ distance_cost 
#define __obfs_8d6a06b2f1208b__ = 
#define __obfs_9529fbba677__ 1, 
#define __obfs_4b04b__ distance_rate 
#define __obfs_8133415ea__ = 
#define __obfs_75806e8__ 0.05; 
#define __obfs_ab2481__ for 
#define __obfs_f3a3a63__ (int 
#define __obfs_a76d__ i 
#define __obfs_7d97667a3e056__ = 
#define __obfs_8430b32b5ba__ 0; 
#define __obfs_5463b514e21fbd3f__ i 
#define __obfs_a19883f__ < 
#define __obfs_e95__ ROW; 
#define __obfs_23755432da68528__ i++) 
#define __obfs_fb4c4__ { 
#define __obfs_d01eeca8b24321c__ final_choice[i] 
#define __obfs_fa8db__ += 
#define __obfs_2766__ this->zombie_cost(i, 
#define __obfs_350a3797c__ zombies_paras, 
#define __obfs_0f9cafd01__ distance_cost, 
#define __obfs_e3b2125__ distance_rate, 
#define __obfs_a3147b8__ NORMAL); 
#define __obfs_ec0f40c389a__ } 
#define __obfs_ad6847__ int 
#define __obfs_9c9f1366edbae758__ plants_num_format[ROW][PLANT_KIND] 
#define __obfs_3b9be7e15b46c4__ = 
#define __obfs_486c825__ {{0}}; 
#define __obfs_02bf8621__ double 
#define __obfs_e1b90__ plants_para[PLANT_KIND] 
#define __obfs_7ac71__ = 
#define __obfs_fc7615__ {8, 
#define __obfs_46123e470d__ -8, 
#define __obfs_d2a2c1da__ -2, 
#define __obfs_73c140__ -2, 
#define __obfs_be93cca18__ -100, 
#define __obfs_ae___ 5}; 
#define __obfs_06f2e099b4f871__ int 
#define __obfs_77340c2e0__ **sum_plants_per_row0 
#define __obfs_101951fe7e__ = 
#define __obfs_64c5__ this->sum_plants_per_row(); 
#define __obfs_3983e1512aa__ for 
#define __obfs_f7___ (int 
#define __obfs_da0b1b5bec71__ i 
#define __obfs_eca89c0554c__ = 
#define __obfs_68897__ 0; 
#define __obfs_a3ec6dd8d53871__ i 
#define __obfs_6abcc8f24321d1eb__ < 
#define __obfs_9ca8c9b0996bbf05__ ROW; 
#define __obfs_5e0__ i++) 
#define __obfs_e910__ { 
#define __obfs_771__ final_choice[i] 
#define __obfs_4ca9764c98c__ += 
#define __obfs_22___ this->plant_cost(i, 
#define __obfs_b2b7c__ sum_plants_per_row0, 
#define __obfs_6f67057__ plants_para, 
#define __obfs_c42f891__ NORMAL); 
#define __obfs_64f07f01__ } 
#define __obfs_fdeea652a89ec3e__ double 
#define __obfs_4ee78d4122ef8503__ time_cost 
#define __obfs_ab24cd2b811ee48__ = 
#define __obfs_a5ff5d4b__ 20 
#define __obfs_1e8ca836c962__ * 
#define __obfs_c1aeb6__ (1 
#define __obfs_de3c1a733c9__ / 
#define __obfs_1b69ebedb5227000__ (1 
#define __obfs_b986700c6__ + 
#define __obfs_c79ec57a8e72a__ exp((this->time 
#define __obfs_6098ed616e71__ - 
#define __obfs_92f__ TOTAL_TIME 
#define __obfs_7dc3338d4__ / 
#define __obfs_5bf__ 2) 
#define __obfs_84f7__ / 
#define __obfs_ca8__ 100)) 
#define __obfs_770c0e7e2a__ - 
#define __obfs_7a6a61__ 0.5); 
#define __obfs_c929f2210__ for 
#define __obfs_0314c9b108b8c39__ (int 
#define __obfs_a4d__ i 
#define __obfs_b2__ = 
#define __obfs_a6a__ 0; 
#define __obfs_46fc943ecd5644__ i 
#define __obfs_93d__ < 
#define __obfs_6734fa703f6__ ROW; 
#define __obfs_88479e328a8633f__ i++) 
#define __obfs_440924__ final_choice[i] 
#define __obfs_4f05d4821fe9967__ += 
#define __obfs_5eb13cb69b6e20d__ time_cost; 
#define __obfs_0777acff7c9ab3__ double 
#define __obfs_6195f47dcff__ sun_baseline 
#define __obfs_60__ = 
#define __obfs_a655fb__ 60, 
#define __obfs_10___ sun_sub 
#define __obfs_d71__ = 
#define __obfs_810dfbbebb173020__ 0.2; 
#define __obfs_2d19__ double 
#define __obfs_8b5c844__ sun_cost 
#define __obfs_9f60ab2b5__ = 
#define __obfs_26ff6f4ca__ (this->Sun 
#define __obfs_37588c65__ - 
#define __obfs_bd22__ sun_baseline 
#define __obfs_18a9042b3fc__ > 
#define __obfs_bba6bca05fecde04__ 0 
#define __obfs_b837305e43f7__ ? 
#define __obfs_3e3aa687__ 1 
#define __obfs_ecf5631507a__ / 
#define __obfs_f816dc__ (1 
#define __obfs_174f8__ + 
#define __obfs_56__ exp((-this->Sun 
#define __obfs_60495b__ + 
#define __obfs_861578d797aeb__ sun_baseline) 
#define __obfs_a7f0d2b95c601__ / 
#define __obfs_65ae450c5536__ 100)) 
#define __obfs_e03845__ * 
#define __obfs_e46bc064f__ 15 
#define __obfs_21__ : 
#define __obfs_adc8ca__ -pow(sun_baseline 
#define __obfs_1bd36c9a__ - 
#define __obfs_8ce__ this->Sun, 
#define __obfs_2130__ 1 
#define __obfs_f69__ / 
#define __obfs_97008ea270__ sun_sub)); 
#define __obfs_16d11e959__ for 
#define __obfs_13b919438__ (int 
#define __obfs_155841__ i 
#define __obfs_91f573__ = 
#define __obfs_96b250a90__ 0; 
#define __obfs_e254457f7497c00f__ i 
#define __obfs_13e5ebb0__ < 
#define __obfs_217f5__ ROW; 
#define __obfs_de043__ i++) 
#define __obfs_b207f5c5__ final_choice[i] 
#define __obfs_0ab922b__ += 
#define __obfs_22cf8d98dca2__ sun_cost; 
#define __obfs_c76db12c8__ this->choice[NORMAL 
#define __obfs_09e7655fc1dc8f__ - 
#define __obfs_77cd__ 1] 
#define __obfs_331cc28f8747a__ = 
#define __obfs_cd474f6341__ this->max_index(final_choice, 
#define __obfs_3770282ae7c0e576__ ROW); 
#define __obfs_99296__ this->value[NORMAL 
#define __obfs_a5e308070bd__ - 
#define __obfs_0fd4b8a8354a77__ 1] 
#define __obfs_2bce32ed409__ = 
#define __obfs_0b0b0__ final_choice[this->choice[NORMAL 
#define __obfs_e0c7ccc4__ - 
#define __obfs_86dba8__ 1]]; 
#define __obfs_0530e__ } 
#define __obfs_7d265aa7__ void 
#define __obfs_7e_____ value_bucket() 
#define __obfs_3335881e0__ { 
#define __obfs_227__ double 
#define __obfs_769ac34a401__ final_choice[ROW] 
#define __obfs_d7b__ = 
#define __obfs_4a71e49f6bd__ {0, 
#define __obfs_590494d54ebe8e__ 0, 
#define __obfs_ef35613fc5fa4c4__ 0, 
#define __obfs_e3b0ab92511ce__ 0, 
#define __obfs_44___ 0}; 
#define __obfs_872__ judge_Lines_not_broken(final_choice); 
#define __obfs_76c__ if 
#define __obfs_1d54c76__ (this->whether_need_compute(BUCKET)) 
#define __obfs_bd85__ { 
#define __obfs_81__ return; 
#define __obfs_d278df491945319__ } 
#define __obfs_d4b__ double 
#define __obfs_35d02fef7d__ zombies_paras[ZOMBIE_KIND] 
#define __obfs_74d90aafda__ = 
#define __obfs_04115ec378e476c__ {2.5, 
#define __obfs_f42a3__ -4, 
#define __obfs_690__ this->time 
#define __obfs_d0ac1ed0__ < 
#define __obfs_82____ 100 
#define __obfs_aafd8346a677a__ ? 
#define __obfs_e464f78__ -100 
#define __obfs_5dcd0ddd3d918c70__ : 
#define __obfs_c0e19ce0dbabb__ -5, 
#define __obfs_dd1016d__ 2, 
#define __obfs_3b24156ad56__ -2}; 
#define __obfs_47257__ double 
#define __obfs_fd45ebc1e1d__ distance_cost 
#define __obfs_8ccfb114__ = 
#define __obfs_70d5212dd052b2e__ 2.5, 
#define __obfs_5d151d1059a62__ distance_rate 
#define __obfs_d40e0a2a__ = 
#define __obfs_887a185b1a40801__ 0.1; 
#define __obfs_fd272fe04b__ for 
#define __obfs_28f72__ (int 
#define __obfs_fe7ecc4de28b2c83__ i 
#define __obfs_5e__ = 
#define __obfs_7369f3c86__ 0; 
#define __obfs_e546594ad40__ i 
#define __obfs_69295f5f6bd__ < 
#define __obfs_f40ee694989b__ ROW; 
#define __obfs_5f24__ i++) 
#define __obfs_8c26d2fad09dc__ { 
#define __obfs_fcac695db02687f__ final_choice[i] 
#define __obfs_608b__ += 
#define __obfs_7bfa32686__ this->zombie_cost(i, 
#define __obfs_6a18__ zombies_paras, 
#define __obfs_29c0c0ee22385__ distance_cost, 
#define __obfs_87d__ distance_rate, 
#define __obfs_ec9__ BUCKET); 
#define __obfs_c5e1ab9c931df8f__ } 
#define __obfs_be3ac64e67e84198__ int 
#define __obfs_094bb65__ plants_num_format[ROW][PLANT_KIND] 
#define __obfs_5101a4796c512__ = 
#define __obfs_13384ffc9d8bdb21__ {{0}}; 
#define __obfs_5d0cb12f8c9ad684__ double 
#define __obfs_33dd6d__ plants_para[PLANT_KIND] 
#define __obfs_dc49__ = 
#define __obfs_53c5b2aff__ {6, 
#define __obfs_0e139b17__ 3, 
#define __obfs_fb___ 2, 
#define __obfs_f0f6cc51dac__ 3, 
#define __obfs_bedc7106ffa9616d__ -100, 
#define __obfs_39b8f__ -4}; 
#define __obfs_05128e4__ int 
#define __obfs_34609bd__ **sum_plants_per_row 
#define __obfs_b1b0ef5ba6b5__ = 
#define __obfs_ddf88ea6__ this->sum_plants_per_row(); 
#define __obfs_eaa__ for 
#define __obfs_9fe4e15b3__ (int 
#define __obfs_18a__ i 
#define __obfs_97e484__ = 
#define __obfs_120ca817ebe8caa7__ 0; 
#define __obfs_55603a5f239e4__ i 
#define __obfs_a732804c8__ < 
#define __obfs_f60ce002e5182e7__ ROW; 
#define __obfs_3e1953b5725__ i++) 
#define __obfs_41b0db49f__ { 
#define __obfs_63cb524a9__ final_choice[i] 
#define __obfs_fa612be4940bae1__ += 
#define __obfs_ccb421d5f36c5a__ this->plant_cost(i, 
#define __obfs_7ec12a__ sum_plants_per_row, 
#define __obfs_2b8f621e9244cea__ plants_para, 
#define __obfs_27584e8__ BUCKET); 
#define __obfs_148d__ } 
#define __obfs_8d8f733a7c2a2e__ double 
#define __obfs_7d___ time_cost 
#define __obfs_11d__ = 
#define __obfs_a57d48399922b034__ 20 
#define __obfs_beda24c1e1b__ * 
#define __obfs_30cde89544__ (1 
#define __obfs_5dd3e474__ / 
#define __obfs_cabad3b9bc0af__ (1 
#define __obfs_ac___ + 
#define __obfs_147540e129e096f__ exp((-this->time 
#define __obfs_b90ba8__ + 
#define __obfs_b052e2e0c0a__ TOTAL_TIME 
#define __obfs_7e889fb76e0e07c1__ / 
#define __obfs_d6cf4da5ce__ 3) 
#define __obfs_b0__ / 
#define __obfs_38087__ 100)) 
#define __obfs_8cb94e7a9661ea20__ - 
#define __obfs_f2b5e92f6__ 0.5); 
#define __obfs_c96c08f8b__ for 
#define __obfs_a7__ (int 
#define __obfs_27d8__ i 
#define __obfs_7716d0fc316__ = 
#define __obfs_2bf7e9e8f3f3bc__ 0; 
#define __obfs_8526e0962a844e4a__ i 
#define __obfs_9a86d53__ < 
#define __obfs_d290__ ROW; 
#define __obfs_3e6ad89fe36__ i++) 
#define __obfs_8e1ad7941398486__ final_choice[i] 
#define __obfs_e0640c__ += 
#define __obfs_d935__ time_cost; 
#define __obfs_31_____ double 
#define __obfs_b5b1d__ sun_baseline 
#define __obfs_f569__ = 
#define __obfs_d3e8fc83b3__ 150, 
#define __obfs_9033__ sun_sub 
#define __obfs_ce0__ = 
#define __obfs_1343777b8ead__ 0.5; 
#define __obfs_2c7f9ccb__ double 
#define __obfs_0d5bd023a3ee1__ sun_cost 
#define __obfs_c6447300d99fdbf4__ = 
#define __obfs_f2c3b258__ (this->Sun 
#define __obfs_40ccca__ - 
#define __obfs_da___ sun_baseline 
#define __obfs_f1676935f9304__ > 
#define __obfs_672d30ab508__ 0 
#define __obfs_583cf6a454__ ? 
#define __obfs_a546203__ 1 
#define __obfs_fead__ / 
#define __obfs_61f3a6dbc9120ea__ (1 
#define __obfs_f291e10e__ + 
#define __obfs_1f5e7f2748adabf__ exp(-this->Sun 
#define __obfs_2000f63__ + 
#define __obfs_3c741__ sun_baseline)) 
#define __obfs_e8aac012__ * 
#define __obfs_e02a35__ 5 
#define __obfs_64b3ec1fdfacead__ : 
#define __obfs_475d66__ -pow(sun_baseline 
#define __obfs_a6d5ab67798__ - 
#define __obfs_244edd7e85dc__ this->Sun, 
#define __obfs_d8a4e572d866aa__ 1 
#define __obfs_b85__ / 
#define __obfs_48a79bcf60__ sun_sub)); 
#define __obfs_46d___ for 
#define __obfs_8710ef761b__ (int 
#define __obfs_a8ef__ i 
#define __obfs_167434f__ = 
#define __obfs_e8432fb72c61c906__ 0; 
#define __obfs_961b2__ i 
#define __obfs_b74084f__ < 
#define __obfs_9c__ ROW; 
#define __obfs_52c670__ i++) 
#define __obfs_c0a62e__ final_choice[i] 
#define __obfs_977b33ace8251dd__ += 
#define __obfs_d3e0f__ sun_cost; 
#define __obfs_db209d71df5__ this->choice[BUCKET 
#define __obfs_1138d90ef0a__ - 
#define __obfs_ae0909a324f__ 1] 
#define __obfs_665d5cbb82b5__ = 
#define __obfs_9ee70b798__ this->max_index(final_choice, 
#define __obfs_1377e22fd810__ ROW); 
#define __obfs_1e51e0__ this->value[BUCKET 
#define __obfs_a118806694c9d__ - 
#define __obfs_526c321538d951f__ 1] 
#define __obfs_f06ae085__ = 
#define __obfs_789a283923__ final_choice[this->choice[BUCKET 
#define __obfs_8f04ac8eadb8__ - 
#define __obfs_50a074e6a__ 1]]; 
#define __obfs_1f187c8bc462__ } 
#define __obfs_2b1905b5d4641__ void 
#define __obfs_d2e__ value_polevault() 
#define __obfs_9bab734__ { 
#define __obfs_6de4bfe9504589a__ double 
#define __obfs_12e59a33d__ final_choice[ROW] 
#define __obfs_65f148__ = 
#define __obfs_4bb94__ {0, 
#define __obfs_6b4e2b9376139__ 0, 
#define __obfs_4738__ 0, 
#define __obfs_0d27688c6__ 0, 
#define __obfs_8fc983__ 0}; 
#define __obfs_41bcfd9ab65__ judge_Lines_not_broken(final_choice); 
#define __obfs_086af__ if 
#define __obfs_03593ce517fe__ (this->whether_need_compute(POLEVAULT)) 
#define __obfs_096__ { 
#define __obfs_f016f25df05b5b1b__ return; 
#define __obfs_b4aa00bc1c59b__ } 
#define __obfs_402b0__ double 
#define __obfs_9dee60d3205c__ zombies_paras[ZOMBIE_KIND] 
#define __obfs_bdb__ = 
#define __obfs_3ce3bd7d63a2c9c8__ {1, 
#define __obfs_2120606d6a__ this->time 
#define __obfs_19485224d__ < 
#define __obfs_702cafa3bb4c9__ 100 
#define __obfs_3d8e03e8b133b16f__ ? 
#define __obfs_bd470ca955d94__ -100 
#define __obfs_ae8__ : 
#define __obfs_0307fec2cef6aec3__ -5, 
#define __obfs_c793b3be8f1__ -1.5, 
#define __obfs_d1f44e2f0__ 2, 
#define __obfs_ea96efc__ -3}; 
#define __obfs_e243a__ double 
#define __obfs_6cf821bc9__ distance_cost 
#define __obfs_aa___ = 
#define __obfs_9d740bd0f36aaa__ 2.5, 
#define __obfs_2bf5e202fc973a02__ distance_rate 
#define __obfs_1da54__ = 
#define __obfs_dc2208f9bbd1148__ 0.1; 
#define __obfs_3bcf__ for 
#define __obfs_65a99bb7a3115__ (int 
#define __obfs_fc8fdb29501a__ i 
#define __obfs_12ced__ = 
#define __obfs_d71f51424__ 0; 
#define __obfs_b4d__ i 
#define __obfs_83451e7ef8755c2a__ < 
#define __obfs_a4d4__ ROW; 
#define __obfs_125c0e943c7__ i++) 
#define __obfs_1d8d70dddf14__ { 
#define __obfs_1f9b616__ final_choice[i] 
#define __obfs_0bd65__ += 
#define __obfs_ce___ this->zombie_cost(i, 
#define __obfs_1713a__ zombies_paras, 
#define __obfs_da9__ distance_cost, 
#define __obfs_60___ distance_rate, 
#define __obfs_3c8__ POLEVAULT); 
#define __obfs_3bc3e78c17d35__ } 
#define __obfs_a1f0cf94512f__ int 
#define __obfs_4bbbe6cb59__ plants_num_format[ROW][PLANT_KIND] 
#define __obfs_b0___ = 
#define __obfs_7c5845__ {{0}}; 
#define __obfs_7f2be1b45d278__ double 
#define __obfs_51a472c08__ plants_para[PLANT_KIND] 
#define __obfs_77305c2__ = 
#define __obfs_3c3c139b__ {5, 
#define __obfs_db____ -2, 
#define __obfs_58079__ -1, 
#define __obfs_0887__ 8, 
#define __obfs_6fd6b030c6afec__ -100, 
#define __obfs_53e19f3dbb211f__ -1}; 
#define __obfs_5ada__ int 
#define __obfs_7230b2b03__ **sum_plants_per_row 
#define __obfs_6d4f95bf53bb__ = 
#define __obfs_1f88c7c5d7__ this->sum_plants_per_row(); 
#define __obfs_fd95e__ for 
#define __obfs_80c94c09__ (int 
#define __obfs_d2b15c75c0c389b__ i 
#define __obfs_8ab8d__ = 
#define __obfs_70afbf2259__ 0; 
#define __obfs_4e2ecebbfafe27a7__ i 
#define __obfs_e9ed9cad56c9__ < 
#define __obfs_61b__ ROW; 
#define __obfs_e0eacd9839716343__ i++) 
#define __obfs_0b5e29a__ { 
#define __obfs_043ab__ final_choice[i] 
#define __obfs_f937c8fddbe66a__ += 
#define __obfs_30da227c6b5__ this->plant_cost(i, 
#define __obfs_4e46e9__ sum_plants_per_row, 
#define __obfs_995__ plants_para, 
#define __obfs_88c040adb393__ POLEVAULT); 
#define __obfs_e0f12__ } 
#define __obfs_a3ab4ff8fa4deed2__ double 
#define __obfs_0fd__ time_cost 
#define __obfs_103__ = 
#define __obfs_f8151fd__ 20 
#define __obfs_0e1feae55e36__ * 
#define __obfs_60dcc0d0012f30__ (1 
#define __obfs_ab6439__ / 
#define __obfs_d03a857a23__ (1 
#define __obfs_2d3b02917ea2900__ + 
#define __obfs_c89ca3__ exp((-this->time 
#define __obfs_34f9a343f945196__ + 
#define __obfs_6c530aae__ TOTAL_TIME 
#define __obfs_cc8__ / 
#define __obfs_4607f7ff__ 5) 
#define __obfs_803ef56843__ / 
#define __obfs_bf499a12e998__ 100)) 
#define __obfs_a4d3a__ - 
#define __obfs_14da92f2bdae__ 0.5); 
#define __obfs_c4819d06b__ for 
#define __obfs_ef0eff608__ (int 
#define __obfs_46489c17893dfdcf__ i 
#define __obfs_a75a52f__ = 
#define __obfs_88____ 0; 
#define __obfs_438124b4c__ i 
#define __obfs_173__ < 
#define __obfs_d84210a75448__ ROW; 
#define __obfs_bdf3fd65c814__ i++) 
#define __obfs_00b7__ final_choice[i] 
#define __obfs_6f3a770e__ += 
#define __obfs_5e51__ time_cost; 
#define __obfs_7d6548bd__ double 
#define __obfs_1a15d41__ sun_baseline 
#define __obfs_76__ = 
#define __obfs_09a__ 120, 
#define __obfs_124461dcd357__ sun_sub 
#define __obfs_14____ = 
#define __obfs_075b24__ 0.4; 
#define __obfs_7d411dca734832__ double 
#define __obfs_2ff385c6e__ sun_cost 
#define __obfs_f8ea2e__ = 
#define __obfs_989652eef28bc49__ (this->Sun 
#define __obfs_475fbefa9ebfb__ - 
#define __obfs_63c4b1baf3b4460__ sun_baseline 
#define __obfs_21___ > 
#define __obfs_e2f374c3418__ 0 
#define __obfs_bf56a1b37b94243__ ? 
#define __obfs_573f7f25b7__ 1 
#define __obfs_710__ / 
#define __obfs_597__ (1 
#define __obfs_bbc92a__ + 
#define __obfs_45e81409831b77__ exp(-this->Sun 
#define __obfs_752d2c9ecfe__ + 
#define __obfs_f110a326be69__ sun_baseline)) 
#define __obfs_8620005ac78d8257__ * 
#define __obfs_37b__ 6 
#define __obfs_9f1f64__ : 
#define __obfs_1dfcb0__ -pow(sun_baseline 
#define __obfs_012__ - 
#define __obfs_591126__ this->Sun, 
#define __obfs_9713faa264__ 1 
#define __obfs_983a33__ / 
#define __obfs_543857f4a06c8__ sun_sub)); 
#define __obfs_1d38dd921e__ for 
#define __obfs_56a8da1d3bcb2__ (int 
#define __obfs_72__ i 
#define __obfs_aee1bc7fa__ = 
#define __obfs_cfb__ 0; 
#define __obfs_26310c700ffd1b5__ i 
#define __obfs_79fde5402cb__ < 
#define __obfs_edb684859b848362__ ROW; 
#define __obfs_0f65caf0a7d00afd__ i++) 
#define __obfs_2f3c6__ final_choice[i] 
#define __obfs_7c33e57e3dbd__ += 
#define __obfs_da974f5eba194__ sun_cost; 
#define __obfs_78f18936__ this->choice[POLEVAULT 
#define __obfs_1f6419b1cb__ - 
#define __obfs_09de__ 1] 
#define __obfs_3910d__ = 
#define __obfs_7a__ this->max_index(final_choice, 
#define __obfs_3eb2f1a06667b__ ROW); 
#define __obfs_62021a1833__ this->value[POLEVAULT 
#define __obfs_19eca5979ccb__ - 
#define __obfs_f8905bd3df64ace__ 1] 
#define __obfs_ccb1d57d7fa17c6__ = 
#define __obfs_e7023__ final_choice[this->choice[POLEVAULT 
#define __obfs_90306a__ - 
#define __obfs_6f518c31f6__ 1]]; 
#define __obfs_359___ } 
#define __obfs_952575__ void 
#define __obfs_a5b93aaec935a__ value_sled() 
#define __obfs_6b0503__ { 
#define __obfs_cb3ce9b__ double 
#define __obfs_4454c95ca2__ final_choice[ROW] 
#define __obfs_d74a21__ = 
#define __obfs_75___ {0, 
#define __obfs_d143__ 0, 
#define __obfs_861637a425ef06e6__ 0, 
#define __obfs_6562c5c1f33d__ 0, 
#define __obfs_bcfa8a78__ 0}; 
#define __obfs_f1920129f9c75b3d__ judge_Lines_not_broken(final_choice); 
#define __obfs_e9dae4__ if 
#define __obfs_bfd2308e9e__ (this->whether_need_compute(SLED)) 
#define __obfs_df__ { 
#define __obfs_0b24d8469d6c__ return; 
#define __obfs_ddac1f6f13bb37__ } 
#define __obfs_31784d9fc1fa0__ double 
#define __obfs_f89394c979b34__ zombies_paras[ZOMBIE_KIND] 
#define __obfs_70b8fe090143d__ = 
#define __obfs_c2890d4__ {3, 
#define __obfs_2f39__ -2, 
#define __obfs_3ac48664b7886c__ -1, 
#define __obfs_c78c347465f477__ -7, 
#define __obfs_f1298750ed096187__ -4}; 
#define __obfs_33805671920f0__ double 
#define __obfs_6ba108__ distance_cost 
#define __obfs_43cf3ae60__ = 
#define __obfs_e2c4__ 2.5, 
#define __obfs_41c__ distance_rate 
#define __obfs_fa1317__ = 
#define __obfs_4ef1477dc9__ 0.1; 
#define __obfs_cfe912f5cb3aa57__ for 
#define __obfs_f58__ (int 
#define __obfs_501627aa14__ i 
#define __obfs_a613863f6a3__ = 
#define __obfs_28659414dab9ec__ 0; 
#define __obfs_2f364281f619584__ i 
#define __obfs_ed46558a56a4a2__ < 
#define __obfs_aaebdb__ ROW; 
#define __obfs_85e5526a360b0__ i++) 
#define __obfs_f0f800c92d1__ { 
#define __obfs_5c3b99e8f9__ final_choice[i] 
#define __obfs_6d0c932802f69__ += 
#define __obfs_fd00d__ this->zombie_cost(i, 
#define __obfs_be7485be5b6eb36__ zombies_paras, 
#define __obfs_d630553e__ distance_cost, 
#define __obfs_971eb27c63__ distance_rate, 
#define __obfs_c850c5__ SLED); 
#define __obfs_f2708856060b3b50__ } 
#define __obfs_3cfacd__ int 
#define __obfs_e661551c8e__ plants_num_format[ROW][PLANT_KIND] 
#define __obfs_70_____ = 
#define __obfs_14f2ebeab937ca12__ {{0}}; 
#define __obfs_000871c1fc726f0b__ double 
#define __obfs_eeaebbffb5d2__ plants_para[PLANT_KIND] 
#define __obfs_0ac0891__ = 
#define __obfs_8011ecba397__ {5, 
#define __obfs_761e6675f9e546__ 10, 
#define __obfs_0397__ 3, 
#define __obfs_b9a8f4af__ 6, 
#define __obfs_1bf2e__ -100, 
#define __obfs_54843973f9b__ 1}; 
#define __obfs_5739fb4e82ed5366__ int 
#define __obfs_e93__ **sum_plants_per_row 
#define __obfs_83__ = 
#define __obfs_9d8__ this->sum_plants_per_row(); 
#define __obfs_1e5186bca8f75f__ for 
#define __obfs_d3f93e7__ (int 
#define __obfs_0d1a9651__ i 
#define __obfs_73634c1dcbe__ = 
#define __obfs_bd5c5e1__ 0; 
#define __obfs_06_____ i 
#define __obfs_3b3fff646346__ < 
#define __obfs_15____ ROW; 
#define __obfs_96__ i++) 
#define __obfs_18fc72d8b8ab__ { 
#define __obfs_1013c8b99e6__ final_choice[i] 
#define __obfs_50adec__ += 
#define __obfs_fcfe9c770e__ this->plant_cost(i, 
#define __obfs_f08__ sum_plants_per_row, 
#define __obfs_33b879e7ab79f56a__ plants_para, 
#define __obfs_080c993fb3b5__ SLED); 
#define __obfs_5ffaa9f5182c2a__ } 
#define __obfs_63c17d596f__ double 
#define __obfs_77c6713209__ time_cost 
#define __obfs_30d411fdc0e6d__ = 
#define __obfs_a4814fbe4abda__ 20 
#define __obfs_50f3f8c42__ * 
#define __obfs_250dd5681__ (1 
#define __obfs_8f4__ / 
#define __obfs_205c__ (1 
#define __obfs_d19544__ + 
#define __obfs_a8f12d9486cbcc__ exp((-this->time 
#define __obfs_d8074a35855a__ + 
#define __obfs_b15__ TOTAL_TIME 
#define __obfs_6ab__ / 
#define __obfs_ab3f9cab2__ 5) 
#define __obfs_555638__ / 
#define __obfs_ec1c5914104__ 200)) 
#define __obfs_cd61a580392a__ - 
#define __obfs_8685549650016d__ 0.5); 
#define __obfs_ee0b86d2__ for 
#define __obfs_f621585d__ (int 
#define __obfs_f64b2463cf1__ i 
#define __obfs_c82a7178ece0__ = 
#define __obfs_fc452__ 0; 
#define __obfs_7c0f63c15__ i 
#define __obfs_9f9e8c__ < 
#define __obfs_fbad540b2__ ROW; 
#define __obfs_6b9bb055__ i++) 
#define __obfs_ccc36675__ final_choice[i] 
#define __obfs_d6____ += 
#define __obfs_722c__ time_cost; 
#define __obfs_85203ae8__ double 
#define __obfs_cfd__ sun_baseline 
#define __obfs_1f5__ = 
#define __obfs_6c2e49911b68d__ 100, 
#define __obfs_ea6979872125d__ sun_sub 
#define __obfs_82_____ = 
#define __obfs_ac4d17__ 0.5; 
#define __obfs_97788__ double 
#define __obfs_4f5c4__ sun_cost 
#define __obfs_d26beb4__ = 
#define __obfs_75____ (this->Sun 
#define __obfs_d1e96978c6935ec0__ - 
#define __obfs_4aaa76178f856__ sun_baseline 
#define __obfs_5265d33c184a__ > 
#define __obfs_3b9d6e5e7__ 0 
#define __obfs_fc152e73692bc3c9__ ? 
#define __obfs_e4a__ 1 
#define __obfs_0e__ / 
#define __obfs_5c645c__ (1 
#define __obfs_ba9fab001f__ + 
#define __obfs_dba1cdfcf635938__ exp(-this->Sun 
#define __obfs_1f____ + 
#define __obfs_c80bcf42c__ sun_baseline 
#define __obfs_5034a5d__ + 
#define __obfs_b7d35509ab19__ 100) 
#define __obfs_700fdb2b__ / 
#define __obfs_1068bceb1__ 200) 
#define __obfs_4772c1b987f1f6d__ * 
#define __obfs_c4414e538a5475__ 10 
#define __obfs_a9ad5f2808f68ee__ : 
#define __obfs_84fdbc__ -pow(sun_baseline 
#define __obfs_ac4395adcb__ - 
#define __obfs_ec___ this->Sun, 
#define __obfs_d33174__ 1 
#define __obfs_daad8d509__ / 
#define __obfs_9fd98f856d3ca208__ sun_sub)); 
#define __obfs_db182d255__ for 
#define __obfs_bc9c8c705927__ (int 
#define __obfs_a7___ i 
#define __obfs_b52340b4de4__ = 
#define __obfs_bd29__ 0; 
#define __obfs_007d4__ i 
#define __obfs_cb59b747__ < 
#define __obfs_5b0fa0e4__ ROW; 
#define __obfs_bc5fcb0018ce__ i++) 
#define __obfs_1a3__ final_choice[i] 
#define __obfs_bb181e83b9a__ += 
#define __obfs_da2__ sun_cost; 
#define __obfs_d71dd235__ this->choice[SLED 
#define __obfs_c47e937423877__ - 
#define __obfs_f1b035b71ef5f__ 1] 
#define __obfs_53420b__ = 
#define __obfs_dd03d__ this->max_index(final_choice, 
#define __obfs_102b905d54a908ae__ ROW); 
#define __obfs_f9___ this->value[SLED 
#define __obfs_6fb52e__ - 
#define __obfs_71f0__ 1] 
#define __obfs_a425__ = 
#define __obfs_13d7dc09__ final_choice[this->choice[SLED 
#define __obfs_096ffc29920__ - 
#define __obfs_fd1d83de25__ 1]]; 
#define __obfs_901797aebf0b23ec__ } 
#define __obfs_37__ void 
#define __obfs_a512294422de868__ value_gargantuar() 
#define __obfs_8df6a65__ { 
#define __obfs_b22ed7eaf__ double 
#define __obfs_c2e0__ final_choice[ROW] 
#define __obfs_f3507289cfdc8c9a__ = 
#define __obfs_0f3__ {0, 
#define __obfs_a55__ 0, 
#define __obfs_a0205__ 0, 
#define __obfs_db9e6eef2eb__ 0, 
#define __obfs_42778ef0b5805__ 0}; 
#define __obfs_01b6__ judge_Lines_not_broken(final_choice); 
#define __obfs_de9051__ if 
#define __obfs_b645e524a1512ce__ (this->whether_need_compute(GARGANTUAR)) 
#define __obfs_b65f2__ { 
#define __obfs_91665__ return; 
#define __obfs_39dd987a9d2__ } 
#define __obfs_ebad33b3__ double 
#define __obfs_91299__ zombies_paras[ZOMBIE_KIND] 
#define __obfs_dfc6__ = 
#define __obfs_84899ae725ba49__ {2, 
#define __obfs_a7____ -4, 
#define __obfs_c678aec6e8__ -5, 
#define __obfs_d80__ -20, 
#define __obfs_0b__ -15}; 
#define __obfs_d914a6c6d9__ double 
#define __obfs_e7d1__ distance_cost 
#define __obfs_0d2b2__ = 
#define __obfs_ea81a__ 2.5, 
#define __obfs_191c__ distance_rate 
#define __obfs_f60f6b0d1__ = 
#define __obfs_cfe795a0a3__ 0.1; 
#define __obfs_9abe36658bff81__ for 
#define __obfs_a3f61f3a8034cbfb__ (int 
#define __obfs_1a77befc3b6__ i 
#define __obfs_dab10c50dc__ = 
#define __obfs_dcf908__ 0; 
#define __obfs_6a57__ i 
#define __obfs_c5d___ < 
#define __obfs_3eae62bba9ddf6__ ROW; 
#define __obfs_8c5ebe8__ i++) 
#define __obfs_538a50f__ { 
#define __obfs_04c690__ final_choice[i] 
#define __obfs_c3___ += 
#define __obfs_085ccaddbd3aa__ this->zombie_cost(i, 
#define __obfs_eafc8fe9c61d67__ zombies_paras, 
#define __obfs_1e__ distance_cost, 
#define __obfs_7a50d__ distance_rate, 
#define __obfs_a376802c0811f1b9__ GARGANTUAR); 
#define __obfs_82______ } 
#define __obfs_5de__ int 
#define __obfs_1d0787d664c95f__ plants_num_format[ROW][PLANT_KIND] 
#define __obfs_1d3b7f1f8a762__ = 
#define __obfs_c5c1bda11__ {{0}}; 
#define __obfs_48c00ae965e23b2__ double 
#define __obfs_6adbe8b2__ plants_para[PLANT_KIND] 
#define __obfs_9a02387b02ce__ = 
#define __obfs_b87517__ {0, 
#define __obfs_4ff3e350028d0cfc__ 100, 
#define __obfs_b28d8e3ccb1f__ 2, 
#define __obfs_18a4e13__ 5, 
#define __obfs_ad____ -100, 
#define __obfs_c96ebeee0519963__ -10}; 
#define __obfs_cede__ int 
#define __obfs_d6317f80523fdf2__ **sum_plants_per_row 
#define __obfs_fecc3a370a23d13__ = 
#define __obfs_0c4a4__ this->sum_plants_per_row(); 
#define __obfs_0c7119e3a6a__ for 
#define __obfs_137bdd55f159c4f5__ (int 
#define __obfs_2912bbeedc16c__ i 
#define __obfs_45c68484c6fc509c__ = 
#define __obfs_a821a161aa__ 0; 
#define __obfs_1cc8a8ea51cd__ i 
#define __obfs_f7dafc__ < 
#define __obfs_22____ ROW; 
#define __obfs_a5bad363fc4__ i++) 
#define __obfs_b112ca4__ { 
#define __obfs_810bf83c7adfd8__ final_choice[i] 
#define __obfs_7c__ += 
#define __obfs_187acf7982__ this->plant_cost(i, 
#define __obfs_084afd913ab1e6ea__ sum_plants_per_row, 
#define __obfs_ed519c02f134f2c__ plants_para, 
#define __obfs_cefb500a__ GARGANTUAR); 
#define __obfs_7e6ff020574__ } 
#define __obfs_e88f243bf__ double 
#define __obfs_30d4__ time_cost; 
#define __obfs_79c__ if 
#define __obfs_85267d349a__ (abs(this->time 
#define __obfs_af8d1eb2201864__ - 
#define __obfs_0f089a__ 500) 
#define __obfs_2edfea__ < 
#define __obfs_9238b8c48__ 25 
#define __obfs_a34e1__ || 
#define __obfs_5857d68cd9280b__ abs(this->time 
#define __obfs_de3f712d1a__ - 
#define __obfs_926ec030f29f83ce__ 1000) 
#define __obfs_7e______ < 
#define __obfs_f720ec3e5486f__ 25 
#define __obfs_0a934__ || 
#define __obfs_41____ abs(this->time 
#define __obfs_40cb22898__ - 
#define __obfs_2054645718__ 1500) 
#define __obfs_768e78024__ < 
#define __obfs_274a10__ 25) 
#define __obfs_bdeeecd97__ time_cost 
#define __obfs_4b0a0290__ = 
#define __obfs_74249__ 100; 
#define __obfs_05ee45de8__ time_cost 
#define __obfs_c4616f5a24a66__ = 
#define __obfs_022400dff__ 100 
#define __obfs_e6cc4__ * 
#define __obfs_1e8eec__ (1 
#define __obfs_ce6babd06__ / 
#define __obfs_038__ (1 
#define __obfs_3e9f0fc9b2f8__ + 
#define __obfs_ec1f764517b__ exp((-this->time 
#define __obfs_549406__ + 
#define __obfs_5d40954183d62__ TOTAL_TIME 
#define __obfs_5cf68969fb67__ / 
#define __obfs_8122__ 5) 
#define __obfs_0c6b6f19684ed9b__ / 
#define __obfs_b8__ 400)) 
#define __obfs_06f__ - 
#define __obfs_6245__ 0.4); 
#define __obfs_aea94dc__ for 
#define __obfs_7aa685b3b1dc1d67__ (int 
#define __obfs_f0bf4a2da952__ i 
#define __obfs_933670f__ = 
#define __obfs_3713bdd__ 0; 
#define __obfs_2cfa8f9e5__ i 
#define __obfs_a68259__ < 
#define __obfs_d91caca74114d81__ ROW; 
#define __obfs_d40__ i++) 
#define __obfs_9ac5a6d86__ final_choice[i] 
#define __obfs_f5e647292cc4e__ += 
#define __obfs_20cf775fa6b5dfe6__ time_cost; 
#define __obfs_3c5__ double 
#define __obfs_a9c397afa__ sun_baseline 
#define __obfs_02b5b45ce743b__ = 
#define __obfs_945__ 550, 
#define __obfs_fb09f481d4__ sun_sub 
#define __obfs_cf040fc710__ = 
#define __obfs_77bdfcf__ 0.6; 
#define __obfs_b71155d90aef3b__ double 
#define __obfs_aa108f56a10e7__ sun_cost 
#define __obfs_606c9__ = 
#define __obfs_2fe5a27c__ 1 
#define __obfs_c6ede20e6f59__ / 
#define __obfs_c348616cd8a86e__ (1 
#define __obfs_1f2b325dcda__ + 
#define __obfs_c133fb1bb634a__ exp(-this->Sun 
#define __obfs_6c35083f35__ + 
#define __obfs_816__ sun_baseline 
#define __obfs_0b081776bae79__ + 
#define __obfs_0b846__ 100) 
#define __obfs_cf63547fadc1aa6__ / 
#define __obfs_060__ 200) 
#define __obfs_e9257036daf2__ * 
#define __obfs_b607a__ 10; 
#define __obfs_68d374__ for 
#define __obfs_723dadb8c69__ (int 
#define __obfs_f083__ i 
#define __obfs_7a9a322cbe0d06__ = 
#define __obfs_001a__ 0; 
#define __obfs_1770ae9__ i 
#define __obfs_3a4__ < 
#define __obfs_b9__ ROW; 
#define __obfs_a08e32d2f9a8b__ i++) 
#define __obfs_e7a425c6ece20cb__ final_choice[i] 
#define __obfs_769c3bc__ += 
#define __obfs_d5036c64412973__ sun_cost; 
#define __obfs_522e1ea43__ this->choice[GARGANTUAR 
#define __obfs_54c3d58c5efcf59__ - 
#define __obfs_0e4ce__ 1] 
#define __obfs_1b33__ = 
#define __obfs_457ded6f20b28fe__ this->max_index(final_choice, 
#define __obfs_43975bc2dfc__ ROW); 
#define __obfs_68abef8ee1ac9__ this->value[GARGANTUAR 
#define __obfs_4a45__ - 
#define __obfs_956685__ 1] 
#define __obfs_86a2f353e1e__ = 
#define __obfs_e4a86__ final_choice[this->choice[GARGANTUAR 
#define __obfs_f5e62af8__ - 
#define __obfs_cf8d8__ 1]]; 
#define __obfs_e7e8f8e5982b32__ } 
#define __obfs_76b7a3a5cf67f3c4__ }; 
#define __obfs_d1942a3ab0__ extern 
#define __obfs_b64a7__ "C" 
#define __obfs_79e785d63f003__ _declspec(dllexport) 
#define __obfs_4fb8a7__ void 
#define __obfs_427e3427c5__ player_ai(IPlayer 
#define __obfs_eaae5e04a259d0__ *player) 
#define __obfs_502cbcfede9f1df__ { 
#define __obfs_50d2d22__ static 
#define __obfs_6e616e79d491ba4__ Game 
#define __obfs_ee39e503b6bed__ game; 
#define __obfs_aba22f748b1a6df__ game.maintain(player); 
#define __obfs_8c53d3__ int 
#define __obfs_b3746__ Type 
#define __obfs_db8419__ = 
#define __obfs_4dc3ed__ player->Camp->getCurrentType(); 
#define __obfs_991327d63593b0ba__ if 
#define __obfs_64a7157cf__ (Type 
#define __obfs_57cd30d908__ == 
#define __obfs_ec16c57ed363__ 0) 
#define __obfs_9a3f263a5e5f__ { 
#define __obfs_2458ab18be2a__ int 
#define __obfs_b43a6403__ NotBrokenLinesNum 
#define __obfs_31bd51a7403b__ = 
#define __obfs_3fc0a5dc1f57__ player->getNotBrokenLines(); 
#define __obfs_3e441eec3__ int 
#define __obfs_db095bd14b8__ KillZombiesScore 
#define __obfs_280c__ = 
#define __obfs_429e4a44bec54__ player->getKillZombiesScore(); 
#define __obfs_5cbb__ int 
#define __obfs_3418__ LeftPlants 
#define __obfs_f6a4f71e72dfe0__ = 
#define __obfs_8cbe9ce__ player->getLeftPlants(); 
#define __obfs_4f____ int 
#define __obfs_4ae1e2b07ec__ Score 
#define __obfs_87ba276ebbe5__ = 
#define __obfs_60ce367__ player->getScore(); 
#define __obfs_d8____ int 
#define __obfs_78e8df__ time0 
#define __obfs_09a8a8976__ = 
#define __obfs_0e64a__ player->getTime(); 
#define __obfs_1216a1__ int 
#define __obfs_04992c5115a2c2__ rows 
#define __obfs_66bf858e1194__ = 
#define __obfs_40170__ player->Camp->getRows(); 
#define __obfs_02052__ int 
#define __obfs_2c6a0bae0f071__ columns 
#define __obfs_30d__ = 
#define __obfs_77d2afcb31f6__ player->Camp->getColumns(); 
#define __obfs_a48251d4c__ int 
#define __obfs_2f3bbb973063__ *PlaceCD 
#define __obfs_f1e___ = 
#define __obfs_a600bd172fcabd__ player->Camp->getPlantCD(); 
#define __obfs_e32c51ad3972__ int 
#define __obfs_33b9c7c18__ **Plants 
#define __obfs_34adeb__ = 
#define __obfs_0f2818101a7ac4b9__ player->Camp->getCurrentPlants(); 
#define __obfs_4fe5149039b5276__ int 
#define __obfs_94bb077f18daa__ ***Zombies 
#define __obfs_10ff0b5e85__ = 
#define __obfs_9f96f36b__ player->Camp->getCurrentZombies(); 
#define __obfs_4ffbd5c8221d7c__ int 
#define __obfs_8396b14__ *LeftLines 
#define __obfs_8e__ = 
#define __obfs_124c3e4__ player->Camp->getLeftLines(); 
#define __obfs_f1ababf130__ int 
#define __obfs_785ca71d2c85e3__ Sun 
#define __obfs_43b9787b8a0cd00a__ = 
#define __obfs_13bf4a9637__ player->Camp->getSun(); 
#define __obfs_fc146be0b230d7e0__ value_plant_func 
#define __obfs_c457d7ae48d08a6b__ value(NotBrokenLinesNum, 
#define __obfs_1f8fe28e9283__ KillZombiesScore, 
#define __obfs_d4b5b5c16__ Score, 
#define __obfs_290ff0feb0__ time0, 
#define __obfs_bf40f0ab4e5e6__ PlaceCD, 
#define __obfs_1fd09c5__ Plants, 
#define __obfs_6dbbe__ Zombies, 
#define __obfs_e586a4f55fb43a54__ LeftLines, 
#define __obfs_ccf8111910__ Sun, 
#define __obfs_2cb__ player, 
#define __obfs_54fe976ba170__ game); 
#define __obfs_a3__ value.make_decision(); 
#define __obfs_03b2__ } 
#define __obfs_415585__ if 
#define __obfs_240ac9371ec__ (Type 
#define __obfs_32___ == 
#define __obfs_1d6408264d31d4__ 1) 
#define __obfs_2c27a260f16ad3__ { 
#define __obfs_351869bde8b9__ int 
#define __obfs_b3848d61bbbc62__ BrokenLinesScore 
#define __obfs_e9470886eca__ = 
#define __obfs_999028872cf__ player->getBrokenLinesScore(); 
#define __obfs_0342c9a7b544__ int 
#define __obfs_f0873a91b49__ KillPlantsScore 
#define __obfs_e140dbab4__ = 
#define __obfs_4424d2d__ player->getKillPlantsScore(); 
#define __obfs_747c1bcceb6109a__ int 
#define __obfs_7e3315fe390974fc__ Score 
#define __obfs_0af78794587__ = 
#define __obfs_714__ player->getScore(); 
#define __obfs_53f___ int 
#define __obfs_b28d7c6b6aec0__ time 
#define __obfs_2f__ = 
#define __obfs_e36258__ player->getTime(); 
#define __obfs_b17c0907e67__ int 
#define __obfs_d62bc__ rows 
#define __obfs_b6e584419__ = 
#define __obfs_f02208a057804e__ player->Camp->getRows(); 
#define __obfs_85___ int 
#define __obfs_bf8dd8c6__ columns 
#define __obfs_ca17__ = 
#define __obfs_faa___ player->Camp->getColumns(); 
#define __obfs_e327b1649__ int 
#define __obfs_a7971abb4134f__ *PlaceCD 
#define __obfs_91c77393975889bd__ = 
#define __obfs_2e2079d633482__ player->Camp->getPlantCD(); 
#define __obfs_aac933717a429f__ int 
#define __obfs_c731__ **Plants 
#define __obfs_97__ = 
#define __obfs_335cd1b90b__ player->Camp->getCurrentPlants(); 
#define __obfs_6651526b6fb8f2__ int 
#define __obfs_79c662560b0a5f1__ ***Zombies 
#define __obfs_c7502c55__ = 
#define __obfs_ba6d843e__ player->Camp->getCurrentZombies(); 
#define __obfs_b6f8dc086b2d60__ int 
#define __obfs_99674__ *LeftLines 
#define __obfs_56bd37d3a2f__ = 
#define __obfs_8cea559c47__ player->Camp->getLeftLines(); 
#define __obfs_1dba3025b15__ int 
#define __obfs_c7b4bb942f0b5d__ Sun 
#define __obfs_9718db12cae6be__ = 
#define __obfs_8977ecbb8__ player->Camp->getSun(); 
#define __obfs_744878fbdd2687__ if 
#define __obfs_86b__ (time 
#define __obfs_4aeae1__ > 
#define __obfs_64ee__ 3) 
#define __obfs_be__ { 
#define __obfs_2654__ int 
#define __obfs_79a3308b13c__ zombie_num 
#define __obfs_7ffb__ = 
#define __obfs_70117ee3c0__ calculate_zombie_nums(Zombies, 
#define __obfs_8d749ea54f665__ 4, 
#define __obfs_f466e84e__ 9); 
#define __obfs_05c7ac946880ad__ value_zombie_func 
#define __obfs_35a0f19__ value(BrokenLinesScore, 
#define __obfs_1e747ddbea997a__ KillPlantsScore, 
#define __obfs_ac____ Score, 
#define __obfs_bdb3c278f45e6__ time, 
#define __obfs_080__ PlaceCD, 
#define __obfs_9f4768b4bd4__ Plants, 
#define __obfs_739cf54211aa6b7__ Zombies, 
#define __obfs_8074856808ebec0c__ LeftLines, 
#define __obfs_785736838d7b51f2__ Sun, 
#define __obfs_a6e8ad49__ zombie_num, 
#define __obfs_4ac7__ game); 
#define __obfs_e1cd50f4a__ value.value_normal(); 
#define __obfs_23685a24__ value.value_bucket(); 
#define __obfs_4a64d9__ value.value_polevault(); 
#define __obfs_2e855f9489df__ value.value_sled(); 
#define __obfs_e1054bf2d7__ value.value_gargantuar(); 
#define __obfs_a0___ int 
#define __obfs_d3f06eef2ff__ decision[2] 
#define __obfs_a4bd4d2__ = 
#define __obfs_fe66__ {0, 
#define __obfs_47e338b3c082__ 0}; 
#define __obfs_a714ec6796f__ value.make_decision(decision); 
#define __obfs_9ce__ if 
#define __obfs_71e63ef5__ (decision[0] 
#define __obfs_043c2ec6c6390d__ != 
#define __obfs_04fcc65450efc__ NOZOMBIE) 
#define __obfs_12b6__ { 
#define __obfs_98c56bce7__ player->PlaceZombie((decision[0] 
#define __obfs_237__ > 
#define __obfs_73d915c91b99__ ZOMBIE_KIND 
#define __obfs_197838c__ ? 
#define __obfs_358f9e7be09177c1__ NORMAL 
#define __obfs_45be58__ : 
#define __obfs_90fd4__ decision[0]), 
#define __obfs_5a9__ decision[1] 
#define __obfs_f5ac21cd0ef1b8__ > 
#define __obfs_6e66329891c__ ROW 
#define __obfs_91bc33__ - 
#define __obfs_48f7d3043bc03e6c__ 1 
#define __obfs_2c___ ? 
#define __obfs_03a3655fff3__ ROW 
#define __obfs_6a6610feab86a__ - 
#define __obfs_91a4d__ 1 
#define __obfs_173f0f__ : 
#define __obfs_9f93557d309f65__ decision[1]); 
#define __obfs_4eff0720836a198__ } 
#define __obfs_7a0c1035bc__ } 
#define __obfs_3f1656d96__ else 
#define __obfs_250b164d84ea39a__ { 
#define __obfs_9a0ee0a9__ player->PlaceZombie(POLEVAULT, 
#define __obfs_2406a0a94c80__ 3); 
#define __obfs_9e95248d9b714a9__ player->PlaceZombie(NORMAL, 
#define __obfs_d32__ 4); 
#define __obfs_878a0658e652__ player->PlaceZombie(BUCKET, 
#define __obfs_ae0e__ 5); 
#define __obfs_4ffb0__ } 
#define __obfs_a5fdfa672284da6__ } 
#define __obfs_fa246d0262c__ } 

__obfs_cfcd208495d__ __obfs_c4ca42__ __obfs_c81e728d__ __obfs_eccbc87e4b5ce2f__ __obfs_a87ff6__ 
__obfs_e4da3b7fb__ __obfs_16790__ __obfs_8f14e45fceea16__ __obfs_c9f0__ __obfs_45__ 
__obfs_d3d9__ __obfs_6512bd43d9ca__ __obfs_c20ad4d76__ __obfs_c51ce410c124a__ __obfs_aab3238922bcc25a__ 
__obfs_9bf31c7ff06__ __obfs_c74d97b01__ __obfs_70e__ __obfs_6f492__ __obfs_1f0e3d__ 
__obfs_98f1370__ __obfs_3c59dc048__ __obfs_b6d7__ __obfs_37693cfc748049e__ __obfs_1ff1de774005__ 
__obfs_8e296a067a3__ __obfs_4e7__ __obfs_02e74f__ __obfs_33e75ff09dd__ __obfs_6ea__ 
__obfs_34173__ __obfs_c16a5320fa4755__ __obfs_6364d3f0f4__ __obfs_182be0c__ __obfs_e369853df76__ 
__obfs_1c3__ __obfs_19ca14e7ea__ __obfs_a5__ __obfs_a5771bce93e200c__ __obfs_d67d8ab4f4__ 
__obfs_d645920__ __obfs_3416a75f4ce__ __obfs_a1d0c6e83f02__ __obfs_17e62166__ __obfs_f7177163__ 
__obfs_6c8349cc7260__ __obfs_d9d4f495e875__ __obfs_67c6__ __obfs_642e92efb7942173__ __obfs_f457c545a9__ 
__obfs_c0c7c__ __obfs_28__ __obfs_9a1158154dfa42c__ __obfs_d82c8d161__ __obfs_a684ece__ 
__obfs_b53b3a3d6a__ __obfs_9f61408e3afb63__ __obfs_72b3__ __obfs_66f04__ __obfs_093f65e080a29__ 
__obfs_072b030__ __obfs_7f39f8__ __obfs_44f683a84163__ __obfs_03afdb__ __obfs_ea5d2f1c460823__ 
__obfs_fc490ca__ __obfs_3295c76ac__ __obfs_735b90b456__ __obfs_a3f39__ __obfs_14bfa__ 
__obfs_7cbbc409ec9__ __obfs_e2c420d928d__ __obfs_32b__ __obfs_d2dd__ __obfs_ad61ab1__ 
__obfs_d09bf__ __obfs_fbd__ __obfs_28dd__ __obfs_35f4a8__ __obfs_d1f__ 
__obfs_f033__ __obfs_43ec517d6__ __obfs_9778d5d__ __obfs_fe9f__ __obfs_68__ 
__obfs_3ef815__ __obfs_93db85ed9__ __obfs_c7e1249ffc__ __obfs_2a38a4a__ __obfs_7647966b7343__ 
__obfs_861__ __obfs_54229a__ __obfs_92cc227532__ __obfs_98dce83da57__ __obfs_f4b9ec30ad9f68f__ 
__obfs_812b4ba287f5e__ __obfs_26657d5ff9__ __obfs_e2ef524fbf3__ __obfs_ed3d__ __obfs_ac627ab1ccbd__ 
__obfs_f899139df5e105__ __obfs_38__ __obfs_ec8956637a997__ __obfs_6974ce5ac6__ __obfs_c9e1074f5b3__ 
__obfs_65b9eea6e1__ __obfs_f0935e4__ __obfs_a97da629b098b75__ __obfs_a3c65c__ __obfs_2723d092b63885e__ 
__obfs_5f93f983524d__ __obfs_698d51a__ __obfs_7f6__ __obfs_73278a4a__ __obfs_5fd0b37cd7__ 
__obfs_2b44928__ __obfs_c45147d__ __obfs_eb160de1de89d__ __obfs_5ef059938ba799a__ __obfs_07e1c__ 
__obfs_da4fb5c__ __obfs_4c56ff4ce4aaf9__ __obfs_a0a080f42e6f__ __obfs_202cb962ac5907__ __obfs_c8ffe9a587b12__ 
__obfs_3def184ad8f4755f__ __obfs_069059b7__ __obfs_ec5dec__ __obfs_76dc611d6eba__ __obfs_d1f491__ 
__obfs_9b8619251a19057__ __obfs_1afa34a7f9__ __obfs_65ded5353__ __obfs_9fc3d715__ __obfs_02__ 
__obfs_7f1de29e6da__ __obfs_42a0e188f__ __obfs_3988c7f88ebcb58__ __obfs_013d40716__ __obfs_e00da__ 
__obfs_1385974ed5904a43__ __obfs_0f28__ __obfs_a8ba__ __obfs_903ce9225__ __obfs_0a09c8844ba8f__ 
__obfs_2b2__ __obfs_a5e00132373a703__ __obfs_8d5e957f__ __obfs_47d1e990583c9c__ __obfs_f2217062__ 
__obfs_7ef605fc__ __obfs_a8f15eda8__ __obfs_37a749d808e4649__ __obfs_b3e3e393c77e3__ __obfs_1d7f7abc18fc__ 
__obfs_2a79ea27__ __obfs_1c9ac015__ __obfs_6c4b761a28b734fe__ __obfs_0640__ __obfs_140f6969d5213fd__ 
__obfs_b73ce398c39f50__ __obfs_bd4c9ab730f5__ __obfs_82__ __obfs_0777d5c17d40__ __obfs_fa7cdfa__ 
__obfs_9766__ __obfs_7e7757b1e12__ __obfs_5878a7ab8__ __obfs_006f52e9102a8d3b__ __obfs_3636638817772e__ 
__obfs_149e9677a5989fd3__ __obfs_a4a042cf__ __obfs_1ff__ __obfs_f7e6__ __obfs_bf8229696f__ 
__obfs_82161242827b7__ __obfs_38af86134b__ __obfs_96da__ __obfs_8f8551796__ __obfs_8f53__ 
__obfs_0451__ __obfs_fc221309746__ __obfs_4c5bde7__ __obfs_cedebb6e87__ __obfs_6cdd60__ 
__obfs_eecca5b63__ __obfs_9872ed__ __obfs_31fefc0e570cb38__ __obfs_9d__ __obfs_a2557a7b2e94197f__ 
__obfs_cfecdb276__ __obfs_0aa1883__ __obfs_58a2fc6ed39fd08__ __obfs_bd686fd__ __obfs_a597e50502f5__ 
__obfs_0336dcb__ __obfs_08__ __obfs_85d8ce590ad__ __obfs_0e6597__ __obfs_84d9ee44e457dde__ 
__obfs_3644a684__ __obfs_757b505cfd34c64__ __obfs_854d6fae5ee42911__ __obfs_e2c0b__ __obfs_27__ 
__obfs_eae27d7__ __obfs_7e__ __obfs_69__ __obfs_091d584__ __obfs_b1d10e7bafa44212__ 
__obfs_6f3ef77ac0e36__ __obfs_eb__ __obfs_1534b76d__ __obfs_979d472a848__ __obfs_ca46c1b9512a__ 
__obfs_3b8a6142__ __obfs_45f__ __obfs_63dc__ __obfs_e96__ __obfs_c0e190d8267e3__ 
__obfs_ec8ce6a__ __obfs_060ad92489947__ __obfs_bcbe3365e6ac95__ __obfs_115f89503138416__ __obfs_13fe__ 
__obfs_d1c38a09acc34__ __obfs_9cfdf10e8fc047a__ __obfs_705f2172__ __obfs_74db120f0a8e5646__ __obfs_57aeee35c98205__ 
__obfs_6da9003b743b6__ __obfs_9b04d15__ __obfs_be83ab3ecd0db__ __obfs_e165421110__ __obfs_289dff07669d7a__ 
__obfs_577__ __obfs_01161aaa0b6d13__ __obfs_539fd__ __obfs_ac__ __obfs_555d67__ 
__obfs_335f5352088d7d9b__ __obfs_f340f1b1f65__ __obfs_e4a6222c__ __obfs_cb__ __obfs_91__ 
__obfs_0266e33d3f546__ __obfs_38d__ __obfs_3cec07e9ba__ __obfs_621bf66ddb7c9__ __obfs_077e29b11be80a__ 
__obfs_6c9882bbac__ __obfs_19__ __obfs_03c6__ __obfs_c24cd76e1ce413__ __obfs_c5__ 
__obfs_fe131__ __obfs_f718499__ __obfs_d96409bf89421768__ __obfs_502e4a16930e41__ __obfs_cfa0860e83a__ 
__obfs_a4f23670e183__ __obfs_b1a59b3__ __obfs_36660e__ __obfs_8c19f571e251__ __obfs_d6baf65e0b240ce1__ 
__obfs_e56__ __obfs_f7664060c__ __obfs_eda80a3d5__ __obfs_8f121__ __obfs_06138bc5af602364__ 
__obfs_39059724__ __obfs_7f1__ __obfs_7a61__ __obfs_47__ __obfs_d947bf0__ 
__obfs_63__ __obfs_db8__ __obfs_20f07591c6fcb220__ __obfs_07c__ __obfs_d395771085__ 
__obfs_92c8c96e4c371__ __obfs_e3796ae__ __obfs_6a9aeddfc68__ __obfs_0f49c89d1e72__ __obfs_46ba9f2a69765__ 
__obfs_0e01938__ __obfs_16a5cdae362b__ __obfs_918317b57931b6b7__ __obfs_48aedb8880c__ __obfs_839ab4682__ 
__obfs_f90f2aca5__ __obfs_9c838d2e45b2ad__ __obfs_1700002963a49da1__ __obfs_53c3__ __obfs_6883966f__ 
__obfs_49182__ __obfs_d296c101daa88a51__ __obfs_9fd81843__ __obfs_26e359e83860db__ __obfs_ef0d3930a7b6c95b__ 
__obfs_94f6d7e04__ __obfs_34ed066df378e__ __obfs_57__ __obfs_11b9842e0a27__ __obfs_37bc__ 
__obfs_496e05e1aea0__ __obfs_b2eb7__ __obfs_8e98__ __obfs_a8c88a0055f__ __obfs_eddea82ad2755b__ 
__obfs_06eb61b__ __obfs_9dfcd5e558dfa0__ __obfs_950a__ __obfs_158f3069a435b__ __obfs_758874998f__ 
__obfs_ad1__ __obfs_3fe94a002317b5f__ __obfs_5b8add2a5d9__ __obfs_432a__ __obfs_8d3bba7425__ 
__obfs_320__ __obfs_caf1a3dfb__ __obfs_5737c6ec2e071__ __obfs_bc__ __obfs_f2f__ 
__obfs_89f0fd5__ __obfs_a666587afda6e89a__ __obfs_b83aac23b9528__ __obfs_cd00692c3bfe592__ __obfs_6faa8040da2__ 
__obfs_fe73f6__ __obfs_6da37dd3139aa4__ __obfs_c0__ __obfs_310__ __obfs_2f2b265625d76a__ 
__obfs_f9b9__ __obfs_685545__ __obfs_357a6fdf7642bf__ __obfs_819f46e52c__ __obfs_04025959b1__ 
__obfs_400__ __obfs_3dd48ab31d0__ __obfs_58238e9ae2dd305d__ __obfs_3ad7c2ebb9__ __obfs_b3967a0e938dc2a6__ 
__obfs_d81f__ __obfs_13__ __obfs_c5ff2543b53f4cc__ __obfs_01386__ __obfs_0bb4aec1__ 
__obfs_9de6d14fff98__ __obfs_efe937780e9557__ __obfs_371bc__ __obfs_138bb0696595__ __obfs_8dd48d6a2e2cad__ 
__obfs_82ce__ __obfs_6c524f__ __obfs_fb7b9ffa5462084c__ __obfs_aa__ __obfs_c05__ 
__obfs_e7b24b112a44fd__ __obfs_52720e003547c__ __obfs_c3e878e27f5__ __obfs_00411460f7c92__ __obfs_bac9162b4__ 
__obfs_9be40cee5b0eee__ __obfs_5ef__ __obfs_05049__ __obfs_cf004fdc76__ __obfs_0c74b7f78409a402__ 
__obfs_d709f38ef75__ __obfs_41f1f19176d38__ __obfs_24b16fe__ __obfs_ffd52f3c7e12435__ __obfs_ad972f1__ 
__obfs_f61d6947467ccd3a__ __obfs_142__ __obfs_d34ab1__ __obfs_8bf1211fd4__ __obfs_a02f__ 
__obfs_bca82e41ee__ __obfs_00ec53c4__ __obfs_4f6ffe1__ __obfs_beed13602b9b0e6__ __obfs_0584ce__ 
__obfs_dc__ __obfs_39461a19e9e__ __obfs_8efb__ __obfs_d9fc5b73a8d78fa__ __obfs_c86a7ee__ 
__obfs_a01a0380ca3c61__ __obfs_5a4b25aaed25c__ __obfs_f73b__ __obfs_70c639df5__ __obfs_28f0b864__ 
__obfs_1543843a4723ed__ __obfs_f8c1f23d6a8d8d__ __obfs_e46de7e1bca__ __obfs_b7b16ecf8ca__ __obfs_352fe25__ 
__obfs_18d8__ __obfs_816b112c6105b__ __obfs_69cb3ea317a32__ __obfs_bbf94__ __obfs_4f4adcbf8c6f6__ 
__obfs_bbcbff5c__ __obfs_8cb22bdd0b7__ __obfs_f4f6dce2__ __obfs_0d0fd7c6e093f7b8__ __obfs_a96b__ 
__obfs_1068c6e4c8051c__ __obfs_17d63b1625c8__ __obfs_b9228e096__ __obfs_0d__ __obfs_66808e327dc7__ 
__obfs_42e7aaa88b48__ __obfs_8fe0093bb30d__ __obfs_41ae__ __obfs_d1f255a373a3ce__ __obfs_7e___ 
__obfs_b6f0479__ __obfs_e0c641__ __obfs_f8__ __obfs_faa9__ __obfs_3c778__ 
__obfs_25b2822c2f5a3__ __obfs_6ecbd__ __obfs_18997733ec258a9__ __obfs_8d7d__ __obfs_75fc09__ 
__obfs_f7490__ __obfs_66368270f__ __obfs_248e84433679__ __obfs_019d385eb67__ __obfs_a49e9411d64f__ 
__obfs_ddb306__ __obfs_24__ __obfs_fccb60__ __obfs_1651cf0d__ __obfs_eed5af6add9__ 
__obfs_a8abb4bb284b5b27__ __obfs_15d4e891d7849__ __obfs_c203d8a15161__ __obfs_13f3cf8c5319__ __obfs_550a141f12de6__ 
__obfs_67f7fb873eaf2952__ __obfs_1a5b1e4d__ __obfs_9a96__ __obfs_9b70e8__ __obfs_d61e4bbd6__ 
__obfs_f5f85__ __obfs_941e1aaaba585__ __obfs_9431c87f273e__ __obfs_49__ __obfs_e44fea__ 
__obfs_821fa7__ __obfs_250cf8b51c77__ __obfs_42998cf32d5__ __obfs_d07e70efcfab0__ __obfs_7fe1f8abaad094e__ 
__obfs_98b2__ __obfs_0353ab4cbed5__ __obfs_51d92__ __obfs_428fc__ __obfs_f1b6f28__ 
__obfs_68ce199ec2c551__ __obfs_e836d__ __obfs_ab817c9349cf9c4f__ __obfs_877a9ba7a9__ __obfs_dc___ 
__obfs_26337353b7962f53__ __obfs_8e6b42f1644ecb__ __obfs_ef575e__ __obfs_2050e03__ __obfs_25ddc0f8__ 
__obfs_5ef0b4__ __obfs_598b3e71ec378bd__ __obfs_7407__ __obfs_cfee398643__ __obfs_d18f65__ 
__obfs_6ea2ef7__ __obfs_9461cce28ebe3e76__ __obfs_f770__ __obfs_e1__ __obfs_eba0dc302bcd9a__ 
__obfs_218a0__ __obfs_7d04bbbe54__ __obfs_a516a87cfc__ __obfs_c3c5__ __obfs_854d9fc__ 
__obfs_c410003__ __obfs_559cb990c9dffd86__ __obfs_55a7cf9c71f1c9c__ __obfs_2f55707d4193d__ __obfs_1be3bc32e6__ 
__obfs_35051070__ __obfs_b534ba68__ __obfs_738__ __obfs_05f971b5ec196b8__ __obfs_3cf166c6b73f__ 
__obfs_cee63__ __obfs_5b69b9cb83__ __obfs_b5b41__ __obfs_285e__ __obfs_b337e84de8752__ 
__obfs_e8c0653fea13f91__ __obfs_ff4d5fbbafdf976c__ __obfs_2d6cc__ __obfs_389bc7bb1e1c2a__ __obfs_e2__ 
__obfs_087__ __obfs_a760880003e7dded__ __obfs_10a7cdd970f__ __obfs_3dc487__ __obfs_59__ 
__obfs_2b8a6__ __obfs_f3f27a__ __obfs_38___ __obfs_ebd9629__ __obfs_63538fe6e__ 
__obfs_cf67355a__ __obfs_07563a__ __obfs_53fde96fcc4b4ce7__ __obfs_2bb232c0b1__ __obfs_ba2fd31__ 
__obfs_69421__ __obfs_85__ __obfs_13f320e7b5__ __obfs_f4be00279e__ __obfs_37f0e884fba__ 
__obfs_d64a340bcb633f5__ __obfs_0fcbc61acd0__ __obfs_298f95e1bf913__ __obfs_df877f3__ __obfs_c399862d3b__ 
__obfs_33__ __obfs_6565__ __obfs_5ea1649a3133609__ __obfs_7bcdf75ad237__ __obfs_5737034557e__ 
__obfs_9b72e31dac81__ __obfs_16c222aa19__ __obfs_7dcd34__ __obfs_814481__ __obfs_97e8527feaf77__ 
__obfs_647bba34__ __obfs_ed265__ __obfs_c75b6f114c23a4d__ __obfs_8d342__ __obfs_ccb1__ 
__obfs_01f78be6f7cad02__ __obfs_7f24d240521d9__ __obfs_94c7bb58efc__ __obfs_f387624df__ __obfs_5e388103a391da__ 
__obfs_15de21c670ae7c__ __obfs_11b921ef__ __obfs_6e2713a6efee__ __obfs_1bb9__ __obfs_3a0772443a0739__ 
__obfs_a9__ __obfs_58ae__ __obfs_4e4b5fbbbb602b__ __obfs_8eefcfdf5990__ __obfs_1728__ 
__obfs_cbcb58ac2e496__ __obfs_db85e2590b6__ __obfs_99__ __obfs_dd458505749b__ __obfs_8b16ebc0__ 
__obfs_a86c450b76fb8c3__ __obfs_c9892a989183de3__ __obfs_e6b4b2a74__ __obfs_e5f6ad6ce374177__ __obfs_f0e52b27a__ 
__obfs_ffeabd2__ __obfs_a7aeed7471411__ __obfs_fde9264cf376fff__ __obfs_a8849b052__ __obfs_258be18e31c8__ 
__obfs_069d3bb__ __obfs_c6e19e830859f2c__ __obfs_46922a0880a8f1__ __obfs_9ad6aaed5__ __obfs_f5deaeeae1538__ 
__obfs_a9a1d5317a33ae8__ __obfs_605ff764c617d3c__ __obfs_766ebcd59__ __obfs_dac__ __obfs_30bb382__ 
__obfs_08b2__ __obfs_3493__ __obfs_dbe272__ __obfs_acc3e040464__ __obfs_076a0c9__ 
__obfs_04ecb1__ __obfs_b2eeb7362ef8__ __obfs_08___ __obfs_6aca9700__ __obfs_3435c378bb76__ 
__obfs_d49__ __obfs_b2f627ff__ __obfs_c3__ __obfs_d8__ __obfs_9cf81d8026a__ 
__obfs_c361bc7b2c033a8__ __obfs_44__ __obfs_dc82d6__ __obfs_996__ __obfs_d7a728a67d90__ 
__obfs_00ac8ed3b4327b__ __obfs_8ebda540cbcc4d73__ __obfs_f76a89f0c__ __obfs_f29c2__ __obfs_851ddf5058cf22__ 
__obfs_58d4d1e7b__ __obfs_7750ca3559e__ __obfs_5d44__ __obfs_eb6fd__ __obfs_cdc0d6e__ 
__obfs_b73dfe25b4b8__ __obfs_85f__ __obfs_3871__ __obfs_a733fa9b25f3368__ __obfs_48ab2f9b4__ 
__obfs_23350907__ __obfs_45645a27c__ __obfs_18__ __obfs_42e77b63637ab3__ __obfs_051e4e127b92f5d__ 
__obfs_9cc138f8dc04cb__ __obfs_b7bb35b9c6__ __obfs_abd815286ba10__ __obfs_26dd0__ __obfs_6766aa2750__ 
__obfs_6a10bb__ __obfs_c5ab__ __obfs_a53__ __obfs_4c27cea8526a__ __obfs_0f96613235__ 
__obfs_4f__ __obfs_67e1__ __obfs_291597a100aadd__ __obfs_9b698__ __obfs_8c7bbbba95c1025__ 
__obfs_5e9f92a01c986ba__ __obfs_0ff39b__ __obfs_303ed4c69846ab36__ __obfs_443cb001c__ __obfs_55b37c5c27__ 
__obfs_884d24__ __obfs_557__ __obfs_30ef30b64204__ __obfs_ea__ __obfs_ab23__ 
__obfs_3d2d8c__ __obfs_26408ffa70__ __obfs_b4288__ __obfs_2f37d1__ __obfs_0ff__ 
__obfs_68264bdb65b97__ __obfs_3a066bda8c96b9__ __obfs_be3159a__ __obfs_8757150de__ __obfs_22__ 
__obfs_84117275b__ __obfs_fae0b27c451c728__ __obfs_b5dc4e5d9__ __obfs_192fc044e74d__ __obfs_5c__ 
__obfs_17c276c8e723eb46__ __obfs_5dd9__ __obfs_2dea61eed4bcee__ __obfs_9f396fe44e7c__ __obfs_0d7de1aca9299__ 
__obfs_8fecb20817b3847__ __obfs_dc6a70712a252123__ __obfs_71a3cb155f8__ __obfs_9fe8593a8__ __obfs_ca9c267__ 
__obfs_fccb3cdc__ __obfs_1595af64350__ __obfs_08d98638c6fcd1__ __obfs_246819284__ __obfs_556f__ 
__obfs_3328__ __obfs_109a0__ __obfs_7f5d04d189dfb6__ __obfs_f79921bbae40a577__ __obfs_07a96b1f61097ccb__ 
__obfs_c06d06da__ __obfs_10a5ab2db37feedf__ __obfs_e555ebe__ __obfs_53e3a71__ __obfs_5487__ 
__obfs_e4bb4c5173c2ce1__ __obfs_0cb929eae7a499__ __obfs_8a0e1141fd__ __obfs_99bcfcd754a9__ __obfs_afd48__ 
__obfs_e5841df2166dd__ __obfs_b4a528955__ __obfs_b1__ __obfs_d6c651dd__ __obfs_f64eac__ 
__obfs_4a4__ __obfs_9c82c7143c102b71__ __obfs_50__ __obfs_ae0eb3eed39d2bc__ __obfs_1ecfb463472ec911__ 
__obfs_e70611883d__ __obfs_60815949__ __obfs_19bc916108fc__ __obfs_07c5807d0d9__ __obfs_d14__ 
__obfs_8df707a948fac1b4__ __obfs_e7__ __obfs_788d9869__ __obfs_50c3d__ __obfs_2afe4567e1bf__ 
__obfs_5f2c22cb4a538__ __obfs_aba3b6fd5d18__ __obfs_c8ed21db4f__ __obfs_084__ __obfs_7f1171a__ 
__obfs_82f2__ __obfs_0d31__ __obfs_fb89705ae6d__ __obfs_d4c2e4a3297__ __obfs_5751ec3e9a__ 
__obfs_d5cfead94f5350c__ __obfs_59c33016884a6__ __obfs_ba386__ __obfs_6c29793a140a8__ __obfs_e995f98d5696__ 
__obfs_6cd67d9b6f01__ __obfs_6bc24fc1ab__ __obfs_a5cdd4aa0048b1__ __obfs_217eedd1ba8c__ __obfs_df263d__ 
__obfs_edfbe1afcf__ __obfs_2e65f__ __obfs_e94550c93c__ __obfs_5c572eca050594__ __obfs_0537fb40a68c1__ 
__obfs_5f__ __obfs_185e65bc405__ __obfs_8d31__ __obfs_e4__ __obfs_b056eb1587586__ 
__obfs_b137__ __obfs_912d2b1c7b28__ __obfs_a1d33d__ __obfs_6f2268b__ __obfs_872488f8__ 
__obfs_ccb0989662__ __obfs_2823f4797102__ __obfs_470e7a__ __obfs_bf62768ca46b__ __obfs_fa14d4fe__ 
__obfs_2ca65f__ __obfs_88ae6372cfdc5d__ __obfs_06__ __obfs_eefc9e10ebdc4a23__ __obfs_58__ 
__obfs_d840cc5d906c3__ __obfs_959__ __obfs_f220__ __obfs_3a__ __obfs_288cc0ff0228__ 
__obfs_4e__ __obfs_b7ee6f5f9__ __obfs_e57c6b956a65__ __obfs_86b12__ __obfs_4e0928de__ 
__obfs_c0f16__ __obfs_8c6744c__ __obfs_f1c1592__ __obfs_e07413354__ __obfs_67__ 
__obfs_a8e864d04c9__ __obfs_7143d7fb__ __obfs_72da7fd6d1302c0a__ __obfs_6e0721b2c6__ __obfs_fc8001f8__ 
__obfs_4b04a686b0ad1__ __obfs_61b4a64b__ __obfs_3621f1454cacf__ __obfs_c15da1f2b__ __obfs_68053af2__ 
__obfs_2dace78f80bc92__ __obfs_df7f28ac89ca__ __obfs_96e__ __obfs_da8ce__ __obfs_8248__ 
__obfs_7c590f01__ __obfs_35cf__ __obfs_beb22fb694d513ed__ __obfs_9e3cfc48__ __obfs_28267__ 
__obfs_7a53928fa4dd__ __obfs_1905a__ __obfs_1141938ba2c2__ __obfs_1aa__ __obfs_dc5689792e08eb2e__ 
__obfs_846c260d715e5b__ __obfs_d58072be2820e86__ __obfs_6e7b33fdea__ __obfs_a8ecbabae151aba__ __obfs_32b30a250abd6331__ 
__obfs_b6edc1cd1f__ __obfs_67___ __obfs_81e74d67858__ __obfs_e0cf1f47118__ __obfs_96b__ 
__obfs_71ad16__ __obfs_43fa7f58b7__ __obfs_31839b036f638__ __obfs_f0adc__ __obfs_3b5d__ 
__obfs_e2a2dcc36a08a345__ __obfs_4558dbb6f6f8b__ __obfs_afda3322__ __obfs_632cee946__ __obfs_677e09724f0e2d__ 
__obfs_d554__ __obfs_795c7a7a5ec__ __obfs_fa3a3c407f8__ __obfs_c2626__ __obfs_ce78d1__ 
__obfs_8e82ab__ __obfs_e0ec4__ __obfs_7250eb93b3c18cc__ __obfs_013a006f03dbc53__ __obfs_301__ 
__obfs_4d5b__ __obfs_ab88b15733__ __obfs_b0b18__ __obfs_f90__ __obfs_8f7d__ 
__obfs_fa83a11a1__ __obfs_02a__ __obfs_fc3cf452d3da8402__ __obfs_3d8e28caf90131__ __obfs_e97ee205__ 
__obfs_b86e8d03f__ __obfs_84__ __obfs_f4552__ __obfs_362e__ __obfs_fe__ 
__obfs_1efa39b__ __obfs_92fb0c6d175826__ __obfs_22ac3c5a5bf__ __obfs_aff__ __obfs_f7e9050c9__ 
__obfs_addfa9b7e234__ __obfs_8c235f89a8143a__ __obfs_847cc55b7032__ __obfs_a67f09__ __obfs_2a084e55c87b1e__ 
__obfs_fc49306d97602__ __obfs_f9a__ __obfs_5ec91aac30ea__ __obfs_19b650660b25__ __obfs_1fc214004c__ 
__obfs_3b3dbaf685__ __obfs_ca__ __obfs_ede7e2b6d13a41dd__ __obfs_dd45045f8c68__ __obfs_49c9adb18e4__ 
__obfs_22fb0cee7e1f3bd__ __obfs_aeb3135b436aa55__ __obfs_43feaeeecd7b2fe__ __obfs_98__ __obfs_51__ 
__obfs_4b0a59ddf11c58__ __obfs_67d16__ __obfs_352407221afb__ __obfs_dd8eb9f23fbd36__ __obfs_d516b136__ 
__obfs_1f5089__ __obfs_7504adad8bb96320__ __obfs_6c3cf77__ __obfs_210f760a89db30aa__ __obfs_17__ 
__obfs_0efe32849d230d__ __obfs_704a__ __obfs_7ce3284b743aefde__ __obfs_0a113__ __obfs_07871915a81071__ 
__obfs_024__ __obfs_cf__ __obfs_c2a__ __obfs_d56b9fc4b0f1be8__ __obfs_4b02507935__ 
__obfs_20__ __obfs_061412e4__ __obfs_5705e1164a8394a__ __obfs_a64c9__ __obfs_0188__ 
__obfs_acf4b89d3__ __obfs_892c91e0a653__ __obfs_b6a1085a27ab7__ __obfs_aa169__ __obfs_f47d0a__ 
__obfs_f57__ __obfs_c8fbbc86__ __obfs_621461af90cadfda__ __obfs_8b6dd7db9af4__ __obfs_a4300b002bcfb71__ 
__obfs_e205ee__ __obfs_b56a__ __obfs_2a9d__ __obfs_8b5040a8__ __obfs_7634ea65a4e__ 
__obfs_248__ __obfs_23ce__ __obfs_da0d1111d2dc5__ __obfs_1e056d2b__ __obfs_3e89ebdb49f7__ 
__obfs_6d0__ __obfs_430c3626b879b__ __obfs_ccc0aa1__ __obfs_c4015b7f368e6b__ __obfs_bea5__ 
__obfs_7fa732b517cb__ __obfs_cbb6a__ __obfs_1f4477b__ __obfs_d045c59a90__ __obfs_0d0871f08__ 
__obfs_1cc363__ __obfs_9f53d83__ __obfs_d2ed45a52__ __obfs_043c3d7e489c6__ __obfs_4daa3db355ef2b0__ 
__obfs_e820a45f1dfc7b95__ __obfs_90794e3b050__ __obfs_b7892fb3c2f00__ __obfs_74bba22728b6185__ __obfs_3df1d4b96d8976__ 
__obfs_8d6dc35e__ __obfs_92262bf__ __obfs_b55ec28c5__ __obfs_2f88__ __obfs_6422__ 
__obfs_4b6538a44a1df__ __obfs_c8c41c4a18675a__ __obfs_c4b31ce7d95c7__ __obfs_58e4d44e550d0f7e__ __obfs_3cef9__ 
__obfs_a3d68b461bd9d35__ __obfs_1c1d4df596d__ __obfs_e6cb2a3c14__ __obfs_9232fe81225__ __obfs_6395ebd0f4b47__ 
__obfs_ef4e3b__ __obfs_168__ __obfs_2ba5__ __obfs_d240e3d__ __obfs_0f__ 
__obfs_437d7d1d97917__ __obfs_d707329bece455a__ __obfs_5c936263f__ __obfs_1c__ __obfs_8065d07da4a7762__ 
__obfs_eeb69a3cb9__ __obfs_4e0c__ __obfs_6cfe0e6127fa__ __obfs_8f468c873__ __obfs_e744f9__ 
__obfs_89fcd07f20b6785b__ __obfs_6602294be91__ __obfs_c22abfa379f3__ __obfs_ca7__ __obfs_4311359ed4969e8__ 
__obfs_92977ae__ __obfs_9c01802ddb981e6b__ __obfs_cc__ __obfs_2ab56412b1163ee__ __obfs_c32d9bf27a3da__ 
__obfs_d79aac075930c83__ __obfs_287e03db1d99e0__ __obfs_fec__ __obfs_6aa__ __obfs_d93ed5b6db83b__ 
__obfs_54a367d6291__ __obfs_fe___ __obfs_df6d233__ __obfs_9908279eb__ __obfs_a1140__ 
__obfs_4fac9ba115140a__ __obfs_692f93b__ __obfs_860320be12a1c050__ __obfs_7b13b2203029e__ __obfs_934815ad542__ 
__obfs_2bcab9d9__ __obfs_0b8aff__ __obfs_ec5aa0b__ __obfs_9ab0d8843__ __obfs_b70683__ 
__obfs_a9b7ba70783b6__ __obfs_b8c37e33defde51c__ __obfs_fba__ __obfs_aa68c75c4__ __obfs_fed3__ 
__obfs_2387337ba1e__ __obfs_9246444d9__ __obfs_d7322ed717dedf__ __obfs_1587965fb4d__ __obfs_31b__ 
__obfs_1e48c4420b70__ __obfs_7f975__ __obfs_f33ba15eff__ __obfs_6b__ __obfs_766d85__ 
__obfs_298923c8190045__ __obfs_08fe2621d8e716b0__ __obfs_5d6__ __obfs_ef__ __obfs_03e0704__ 
__obfs_65cc2c8205a05d7__ __obfs_0768281a05da9__ __obfs_93d65641ff3f1__ __obfs_ce5140df15d04__ __obfs_021bb__ 
__obfs_82b8__ __obfs_24___ __obfs_88__ __obfs_3806734b256c27e4__ __obfs_84d__ 
__obfs_e515df0d20__ __obfs_afdec7005cc9f1__ __obfs_995e1fda4__ __obfs_e1___ __obfs_bdb106a0560c4e__ 
__obfs_a34bacf__ __obfs_83fa5a432ae55__ __obfs_eddb90__ __obfs_6d70cb65d15211__ __obfs_27ed0fb950b856b0__ 
__obfs_537d9b6__ __obfs_d736bb10d83a904a__ __obfs_9a__ __obfs_b9141aff1412dc76__ __obfs_1019c8091693__ 
__obfs_a0e2__ __obfs_1579779b98__ __obfs_20b5e1__ __obfs_7cce53cf90577__ __obfs_58c54802a9fb9526__ 
__obfs_50___ __obfs_45___ __obfs_f4dd765c1__ __obfs_7fe__ __obfs_db576a7d24535__ 
__obfs_53c__ __obfs_4ca82782c5372a5__ __obfs_d8700cbd3__ __obfs_b4d168b48__ __obfs_4a08142__ 
__obfs_29__ __obfs_a89cf525__ __obfs_cd89fef__ __obfs_6c340f__ __obfs_2290a7__ 
__obfs_a2137a2ae8e39__ __obfs_43dd49b4fdb9b__ __obfs_31857b449c40__ __obfs_53adaf494__ __obfs_fc2c7c4__ 
__obfs_dc58e3a306451c9d__ __obfs_1b0114c51cc532e__ __obfs_a1519de5b5__ __obfs_390__ __obfs_708f3cf__ 
__obfs_46072631582f__ __obfs_8a1e808b5__ __obfs_062ddb6c72__ __obfs_522a9ae__ __obfs_43baa676__ 
__obfs_731c83db8d2ff01__ __obfs_36a16a25053__ __obfs_818f4654ed39a__ __obfs_e5e63da79fcd2b__ __obfs_9f36407ead06__ 
__obfs_4f16c818875d__ __obfs_d91d1b4d82419de__ __obfs_a263__ __obfs_b1___ __obfs_03f5446139179452__ 
__obfs_8b__ __obfs_754dda4b__ __obfs_6a2fee__ __obfs_68b1__ __obfs_41bfd20a38bb1b0__ 
__obfs_d6723e7__ __obfs_4e___ __obfs_db2b4__ __obfs_a5e0ff__ __obfs_a0160709701140__ 
__obfs_1e6__ __obfs_c6bff625bdb0393__ __obfs_c667__ __obfs_aace49c7d80767cf__ __obfs_4da04049a__ 
__obfs_af21d0c__ __obfs_c9__ __obfs_e58cc5ca942__ __obfs_b9d487a30398__ __obfs_8f1d43620b__ 
__obfs_2cbca44843__ __obfs_b59__ __obfs_20d135f0f28185b8__ __obfs_9c3b__ __obfs_d6ef5f7fa914c19__ 
__obfs_e19__ __obfs_dd77279__ __obfs_0eec27c419d0fe24__ __obfs_c60d060__ __obfs_8597a6c__ 
__obfs_c6036a69be21cb66__ __obfs_3a15c7d0bbe__ __obfs_3b712de__ __obfs_2cfd4560539f8__ __obfs_c7635bfd99__ 
__obfs_c21__ __obfs_ffeed84c7c__ __obfs_678a1491514b7__ __obfs_3fe78a8acf5fda__ __obfs_69a5b5995110b36a__ 
__obfs_4a213d37242bdca__ __obfs_fe709c654e__ __obfs_571e0f7e2d992e__ __obfs_fd0__ __obfs_7c9__ 
__obfs_fd2c5e468__ __obfs_47a__ __obfs_801c14f07f__ __obfs_c3e0c62ee91db8d__ __obfs_1842603__ 
__obfs_8248a99e81e75__ __obfs_f7f580e11d00a__ __obfs_8ce6790c__ __obfs_208e4__ __obfs_4588e6__ 
__obfs_feab05aa91085b7__ __obfs_8a__ __obfs_a1d50185e7426cb__ __obfs_df0a__ __obfs_09c6c3783b__ 
__obfs_2b3__ __obfs_f197002b9__ __obfs_45f31d16b1058__ __obfs_55b__ __obfs_e8b1cbd05f6e6a35__ 
__obfs_285f89b802bcb2__ __obfs_e22312179bf43e__ __obfs_a8240cb82__ __obfs_0c048b3a434e49__ __obfs_16e6a3__ 
__obfs_884d79963bd__ __obfs_38ca895__ __obfs_abea47ba24__ __obfs_6e7d2da6d3953__ __obfs_00e26af6a__ 
__obfs_a3fb4f__ __obfs_0f2c9a93ee__ __obfs_9da__ __obfs_2f29b6e__ __obfs_1e1d184167ca__ 
__obfs_3eb71f62__ __obfs_a113c1ec__ __obfs_36a1694bce9815b__ __obfs_0a0a0__ __obfs_3473decccb__ 
__obfs_1896a3bf730516__ __obfs_a7d8__ __obfs_83f97f48252__ __obfs_7d__ __obfs_dabd8d2ce74e__ 
__obfs_6eb6e75fddec__ __obfs_2ac24__ __obfs_f473306__ __obfs_0e095e054ee9477__ __obfs_97af4fb322__ 
__obfs_568__ __obfs_2b6d65b9__ __obfs_4f28480__ __obfs_c44e503833b6__ __obfs_82c255__ 
__obfs_160c88652d47d0be__ __obfs_b20bb95ab626d__ __obfs_52292e0c763__ __obfs_9a3d458322__ __obfs_a42a596__ 
__obfs_0188e8b8b014829e__ __obfs_9adeb82fffb54__ __obfs_ae5e3ce__ __obfs_c54e7837e0c__ __obfs_4d2e7bd33c475__ 
__obfs_fe2d010__ __obfs_7501e5d4da87__ __obfs_14770__ __obfs_491442df__ __obfs_fb2fcd534b0__ 
__obfs_b571ecea1__ __obfs_144a3f71a03ab7__ __obfs_4e4e53aa080247b__ __obfs_a58149d355f02__ __obfs_7e7e69ea3384__ 
__obfs_f7cade80b7cc92b__ __obfs_285ab9448d2__ __obfs_a016__ __obfs_33ceb07bf4ee__ __obfs_c8__ 
__obfs_a4d2__ __obfs_3948ead6__ __obfs_6a61d423d02a1__ __obfs_3f67fd9716__ __obfs_27155__ 
__obfs_b24d516bb65a5a__ __obfs_1d72310edc006dad__ __obfs_3a029f04d76d3__ __obfs_43cca4__ __obfs_68___ 
__obfs_25df__ __obfs_3210ddbeaa16948a__ __obfs_c4851__ __obfs_eb86d510361fc23b__ __obfs_310c__ 
__obfs_41__ __obfs_6c1__ __obfs_e53a0a297__ __obfs_e034fb6b66a__ __obfs_81dc9bdb52d0__ 
__obfs_9996535e07258a__ __obfs_7bcc__ __obfs_a9eb8__ __obfs_d3890__ __obfs_b3ba8f1bee__ 
__obfs_a9078e8653368c9__ __obfs_1c65cef3dfd1__ __obfs_2de5d166__ __obfs_e1d5be1c7__ __obfs_2c89109d421__ 
__obfs_5eac43ac__ __obfs_905056c1ac1dad1__ __obfs_e6d8545daa42d5__ __obfs_39e4973ba3321__ __obfs_2ba8698b7943958__ 
__obfs_81e5f8__ __obfs_838e__ __obfs_a284d__ __obfs_b495__ __obfs_884ce4bb65d__ 
__obfs_3bf55bbad370__ __obfs_e3251075__ __obfs_cd__ __obfs_26588e932__ __obfs_68a__ 
__obfs_f4__ __obfs_17326d10d__ __obfs_dc4c4__ __obfs_7eb__ __obfs_6c8dba7d0df1c4a7__ 
__obfs_0c__ __obfs_8e2cfdc275761__ __obfs_b51a15f382ac914__ __obfs_19___ __obfs_e00406144c1__ 
__obfs_c850371f__ __obfs_c1e39d912d21c9__ __obfs_781__ __obfs_f91e24dfe__ __obfs_e702e5__ 
__obfs_bb04a__ __obfs_fb60d4__ __obfs_d759175de8ea5b1__ __obfs_ab1a4d0dd4d48a2__ __obfs_99566__ 
__obfs_da11e8cd181__ __obfs_d94e__ __obfs_1ce__ __obfs_018b59ce__ __obfs_242c__ 
__obfs_944__ __obfs_c0a271__ __obfs_40790__ __obfs_0e9fa1f3e9__ __obfs_0829424ffa0d3__ 
__obfs_70222949cc0__ __obfs_71f6278d140af__ __obfs_459a4ddcb5__ __obfs_7c82fab8c8__ __obfs_84438b7aae__ 
__obfs_dc87c13749315__ __obfs_2812e5cf6d8f21d6__ __obfs_2866__ __obfs_a51fb975227d6__ __obfs_a0833c8a1__ 
__obfs_6f__ __obfs_2df__ __obfs_996009f2374__ __obfs_d282ef263719ab8__ __obfs_5ca__ 
__obfs_fd5c90__ __obfs_7940ab4746__ __obfs_f9__ __obfs_a0872cc__ __obfs_447__ 
__obfs_535ab76633d94__ __obfs_7bb0607__ __obfs_f29b38f160f87ae8__ __obfs_f0969691__ __obfs_50905d7b__ 
__obfs_dfd7468ac613286__ __obfs_f3f1b7fc5a8779__ __obfs_93fb9__ __obfs_76cf99d3614e23ea__ __obfs_1ee3__ 
__obfs_2a50e9c__ __obfs_f9be311e__ __obfs_dc960c46c38b__ __obfs_4671aeaf49__ __obfs_bb7946e7d8__ 
__obfs_3546ab4__ __obfs_c70daf24__ __obfs_17___ __obfs_4c22bd444899d3__ __obfs_01e95__ 
__obfs_fe515__ __obfs_e077e1a544__ __obfs_28e2__ __obfs_ff49cc40a__ __obfs_8edd72158ccd2a__ 
__obfs_9cb__ __obfs_3d77__ __obfs_e4___ __obfs_05311655a1__ __obfs_d10ec7c16cbe__ 
__obfs_4f87658ef0de1__ __obfs_33e__ __obfs_5e1b18c__ __obfs_674bfc5f6__ __obfs_a50abba8132a7719__ 
__obfs_86109d400f0ed2__ __obfs_82965d4e__ __obfs_0e5566__ __obfs_c73dfe6c63__ __obfs_bcc0d4002__ 
__obfs_861dc9b__ __obfs_3e313b__ __obfs_8b0dc65f996__ __obfs_ee8374ec4e__ __obfs_af473271166105__ 
__obfs_b8c27b7a1c450ff__ __obfs_980ecd059122c__ __obfs_c2__ __obfs_83adc9225e4d__ __obfs_8d3369c4c086__ 
__obfs_fb__ __obfs_cf9a242b7__ __obfs_a9be4c2a4041__ __obfs_9683cc__ __obfs_effc299a1a__ 
__obfs_cf1f78fe923afe05__ __obfs_6a5__ __obfs_a2__ __obfs_6c1da886822c__ __obfs_0e3a37aa8__ 
__obfs_d1ee59e20ad0__ __obfs_81ca0262c82__ __obfs_f3bd5ad57c__ __obfs_e56b06c__ __obfs_792c7b5__ 
__obfs_70__ __obfs_79a49b__ __obfs_f523__ __obfs_8d9a0adb7c204239__ __obfs_bad5f33__ 
__obfs_ea8fcd92d59__ __obfs_d82118376df34__ __obfs_4e0d67e54ad__ __obfs_cd0dce8fca267b__ __obfs_5ca3e9b1__ 
__obfs_86e8f7ab32cfd__ __obfs_363763__ __obfs_4f___ __obfs_0c0a7__ __obfs_2bd7f__ 
__obfs_359f38463d__ __obfs_7f53__ __obfs_c0826819636026__ __obfs_ad__ __obfs_f016e59c7ad8b1d7__ 
__obfs_14d9e8007c9__ __obfs_09662890__ __obfs_215__ __obfs_d97313__ __obfs_602d1305678a__ 
__obfs_f0dd4a99fba6075a__ __obfs_9701a1c165dd94__ __obfs_28fc2782ea7e__ __obfs_4ed__ __obfs_186a157b2992__ 
__obfs_3de2334a314__ __obfs_b7087c1f4__ __obfs_46771d1f432b4__ __obfs_6d9c__ __obfs_7b5b23f4aa__ 
__obfs_512c5ca__ __obfs_54072f485cdb789__ __obfs_0e4e946668cf2__ __obfs_59f51fd693741__ __obfs_7a674153c__ 
__obfs_a60937eba__ __obfs_23ad3e31__ __obfs_9a17__ __obfs_309__ __obfs_30c8e1ca87252__ 
__obfs_90db9da__ __obfs_9aa42b31882e__ __obfs_0ed9422357395__ __obfs_856__ __obfs_489d0396e6826eb__ 
__obfs_a424ed4__ __obfs_299f__ __obfs_970af__ __obfs_0663a4__ __obfs_56352739f5964354__ 
__obfs_411ae1bf081d167__ __obfs_e11943a6031__ __obfs_56468d5607a5aa__ __obfs_b069b3__ __obfs_78__ 
__obfs_1f3202d820180a__ __obfs_eaa32c96f620053c__ __obfs_a8f8f6026__ __obfs_db6ebd__ __obfs_540ae6b0f6ac6e15__ 
__obfs_f4a331b__ __obfs_b197ffdef2d__ __obfs_f69e__ __obfs_8fb5f8be2aa9d6c6__ __obfs_afe434653a898da__ 
__obfs_b265ce60fe4c53__ __obfs_8fb21ee7a22__ __obfs_c930eecd01935fee__ __obfs_e94f63f57__ __obfs_2dffbc474aa1__ 
__obfs_c5cc17e395d30__ __obfs_80a8155e__ __obfs_6786__ __obfs_53__ __obfs_3bbfdde8842a__ 
__obfs_0a1bf96b7__ __obfs_5e76__ __obfs_01d8b__ __obfs_4d__ __obfs_1abb1e1ea5__ 
__obfs_07042ac7__ __obfs_95151403b0__ __obfs_ad71c__ __obfs_fe70c3__ __obfs_c913303f__ 
__obfs_372d3f30__ __obfs_6d9__ __obfs_0245952ecff55018__ __obfs_cec6f62cfb44__ __obfs_991de292__ 
__obfs_42f__ __obfs_8b0d2__ __obfs_da__ __obfs_ac796__ __obfs_7d6044e95a1__ 
__obfs_571d3a9420__ __obfs_97275a23ca__ __obfs_78b__ __obfs_83cdcec08fbf903__ __obfs_dc09c97f__ 
__obfs_e816c635cad__ __obfs_4e8412ad4__ __obfs_ab5__ __obfs_bff__ __obfs_729c68884bd__ 
__obfs_7fb__ __obfs_86df7dcfd8__ __obfs_6d3a1e06d6a0634__ __obfs_8a146f1a3__ __obfs_1baff70e2669e8__ 
__obfs_f187a__ __obfs_226d1f15ecd35f7__ __obfs_e655c7716a4b3e__ __obfs_1714726c817__ __obfs_fcdf25d6e191893__ 
__obfs_fa1e__ __obfs_1415db70fe9__ __obfs_55c5__ __obfs_ced__ __obfs_6490791e7__ 
__obfs_cf___ __obfs_5cbdfd__ __obfs_77f95__ __obfs_0c8ce55163055c4d__ __obfs_49b8b4f95__ 
__obfs_0c9e__ __obfs_b5488aeff__ __obfs_4dcf43543__ __obfs_ebd6d2f5d60f__ __obfs_1cd388239452087__ 
__obfs_41a60377ba920919__ __obfs_ebb7104545__ __obfs_0f3d014ee__ __obfs_2b3bf3eee__ __obfs_83f2550__ 
__obfs_bc___ __obfs_490__ __obfs_81c8__ __obfs_42d6c7d61481d__ __obfs_5607fe8879__ 
__obfs_db1915052d15f781__ __obfs_253f__ __obfs_3fb451__ __obfs_df12ecd07__ __obfs_471c75__ 
__obfs_8c00dee24c987__ __obfs_e60e81c4cb__ __obfs_5cce8dede__ __obfs_109d2__ __obfs_aa48__ 
__obfs_cb8acb1dc9821bf__ __obfs_99ad__ __obfs_0804083__ __obfs_35309226eb45ec__ __obfs_d63fbf8c31737__ 
__obfs_748ba69d3e__ __obfs_b5a1fc208598603__ __obfs_d1a__ __obfs_b60c5a__ __obfs_17e__ 
__obfs_cda72177eba360f__ __obfs_1373b2__ __obfs_d01__ __obfs_819c9fbfb0__ __obfs_f337d999d9__ 
__obfs_89ae0__ __obfs_aff0a6a45212329__ __obfs_204da25__ __obfs_35464c__ __obfs_c88d8d0a60977__ 
__obfs_6b8eba43__ __obfs_4e6cd95227cb__ __obfs_351b33587c5fdd__ __obfs_18e__ __obfs_9898__ 
__obfs_b2dd140336c9d__ __obfs_4e9cec__ __obfs_596f713f9a737__ __obfs_2992__ __obfs_020c8bfac__ 
__obfs_3a20f62a0af1aa1__ __obfs_b132ecc1609b__ __obfs_92af__ __obfs_4d6e4749__ __obfs_facf9f74__ 
__obfs_d961__ __obfs_be53ee611049__ __obfs_18d10dc__ __obfs_dfa92d8f817__ __obfs_655__ 
__obfs_794__ __obfs_7bd28f15a49d5e5__ __obfs_45____ __obfs_a1af__ __obfs_0d4f480__ 
__obfs_70ef__ __obfs_af__ __obfs_7e1d842d0f7__ __obfs_95__ __obfs_ed4227734ed__ 
__obfs_dc____ __obfs_88a1__ __obfs_b71091__ __obfs_076023__ __obfs_27728__ 
__obfs_228499b55310264a__ __obfs_8f__ __obfs_49a__ __obfs_894b77f805bd94__ __obfs_dca5672f__ 
__obfs_bcb41ccdc4363c__ __obfs_5129a5ddcd0dcd7__ __obfs_d72fbbccd9f__ __obfs_06a81a4fb98d1__ __obfs_0ebcc77dc72360d__ 
__obfs_d88518__ __obfs_309fee4e5__ __obfs_87ec2f451208__ __obfs_9c19a2aa1d8__ __obfs_83e8ef5__ 
__obfs_9e984c10815__ __obfs_c559da2ba96__ __obfs_1bc02__ __obfs_f3173935ed8ac__ __obfs_a368b0__ 
__obfs_f18a6d1cde4b205__ __obfs_495dabfd0ca768__ __obfs_959735__ __obfs_faafda66202d2344__ __obfs_a2cc63e06__ 
__obfs_a14ac55__ __obfs_7a6a74cbe87bc__ __obfs_52947e0ade57a__ __obfs_69d658__ __obfs_e9fd__ 
__obfs_71a58e__ __obfs_962e56a8__ __obfs_297__ __obfs_f60bb6bb4c96d4df__ __obfs_d1dc3a8270a6f9__ 
__obfs_806beafe1__ __obfs_4462bf0ddb__ __obfs_c7a__ __obfs_fc528592c385__ __obfs_93__ 
__obfs_a981f2b70__ __obfs_bc573864331a9__ __obfs_97d0145823__ __obfs_efb76cff97__ __obfs_5c50b4df4b1768__ 
__obfs_46031b3d04dc909__ __obfs_6ba__ __obfs_0771fc6f0f4__ __obfs_21fe5b8ba755eea__ __obfs_6dd4e10e3296fa63__ 
__obfs_42a396__ __obfs_1c54__ __obfs_52c5__ __obfs_7e230522657__ __obfs_3c1e4bd671__ 
__obfs_84f0f20__ __obfs_10c272d06794d3__ __obfs_81c650caac28c__ __obfs_f670ef5d2d6__ __obfs_89f03f7d02__ 
__obfs_c1fea270c__ __obfs_e4873aa9a0__ __obfs_8d420f__ __obfs_7437d136770f5b3__ __obfs_96de2547__ 
__obfs_973a5f0ccb__ __obfs_be3e9d3f7d705__ __obfs_207f880__ __obfs_b147__ __obfs_9d2682367c3935__ 
__obfs_cc___ __obfs_712a3c9__ __obfs_a40511cad8383e5__ __obfs_c0560792e4__ __obfs_e16960__ 
__obfs_9a4400__ __obfs_7d12b66d3df6af8d__ __obfs_b2531e__ __obfs_e449b9317da__ __obfs_4f398cb9d6bc7__ 
__obfs_e8d92f99e__ __obfs_86d7c8a08b4aaa1b__ __obfs_15__ __obfs_b0f2ad44d26e1a6f__ __obfs_cd___ 
__obfs_148__ __obfs_647c7__ __obfs_24____ __obfs_a0f__ __obfs_757f843a169__ 
__obfs_64f1f27bf1b4e__ __obfs_831c2f8__ __obfs_08e6be__ __obfs_2cb6b10338a7fc__ __obfs_e638471149171__ 
__obfs_11d0e6287202__ __obfs_f50a6c02a3fc5a__ __obfs_6a816__ __obfs_fd__ __obfs_1ef91c212e__ 
__obfs_5d__ __obfs_b618c3210e__ __obfs_7fea637fd__ __obfs_ae614c557__ __obfs_7c4ede__ 
__obfs_d43ab110ab__ __obfs_8303a79b1e19a__ __obfs_4921f95ba__ __obfs_b59a51a3c0bf9c__ __obfs_26751be11814__ 
__obfs_e721a54a8cf1__ __obfs_5cf21ce__ __obfs_673271cc47c1a4__ __obfs_9f__ __obfs_ef2a4be5473__ 
__obfs_01e00f2f4bfcbb75__ __obfs_15231a7ce4ba789__ __obfs_b9f94c77652c__ __obfs_375c__ __obfs_a588a6__ 
__obfs_2a27b8144ac02f67__ __obfs_8bb88f80d__ __obfs_02f0__ __obfs_c59b469__ __obfs_52d080a3e172c33__ 
__obfs_5a142__ __obfs_a941493ee__ __obfs_a51c896c__ __obfs_464d__ __obfs_798e__ 
__obfs_0efbe98067__ __obfs_66be31e4__ __obfs_8b5__ __obfs_fc6709__ __obfs_f3144cefe8__ 
__obfs_acab011__ __obfs_28dc6b0__ __obfs_404dcc9__ __obfs_8725fb777f__ __obfs_62__ 
__obfs_3e7e02__ __obfs_7456__ __obfs_51___ __obfs_7137debd45ae__ __obfs_25e2a30__ 
__obfs_851300ee84__ __obfs_b29eed44276__ __obfs_270edd69788d__ __obfs_4fa53be91b4933d__ __obfs_ab2__ 
__obfs_c4492cbe90fbdb__ __obfs_c0___ __obfs_70ece1e1e0931919__ __obfs_84c6494d30851c__ __obfs_752d25a1f8dbfb2__ 
__obfs_54f__ __obfs_b3b43a__ __obfs_6e62__ __obfs_955a158__ __obfs_418ef6127e__ 
__obfs_97d9811903__ __obfs_442cd__ __obfs_3e15cc11f9__ __obfs_54e36c5ff5__ __obfs_fc9b003b__ 
__obfs_6a5dfac4b__ __obfs_b3bbccd6c0__ __obfs_11c4__ __obfs_a63fc8c5__ __obfs_231141b34c8__ 
__obfs_d8d31bd778da__ __obfs_ce__ __obfs_d2cdf047a66__ __obfs_261__ __obfs_ba1__ 
__obfs_e22dd5dabde45ed__ __obfs_7283518d47a0__ __obfs_17e___ __obfs_df9028fcb6b0__ __obfs_94e445__ 
__obfs_8698ff92115213a__ __obfs_96a93__ __obfs_e8fd4a8a5ba__ __obfs_db__ __obfs_7eb7eabbe9b__ 
__obfs_e5a__ __obfs_21be9a__ __obfs_299570476__ __obfs_4abe__ __obfs_f0bda__ 
__obfs_36d7534290610d__ __obfs_7dd0__ __obfs_e9b73b__ __obfs_6709e8d6__ __obfs_8c01a75__ 
__obfs_f63f65b503e2__ __obfs_8b6a80c3cf2cbd__ __obfs_4a2ddf148c5a9__ __obfs_b865367__ __obfs_365d17770080c80__ 
__obfs_393c55aea738548__ __obfs_6449f44a102__ __obfs_d860bd1__ __obfs_db957c626a8cd7a2__ __obfs_ecd62de20ea67e1__ 
__obfs_d25414__ __obfs_bf201d540__ __obfs_052335232b1__ __obfs_c8cbd__ __obfs_59e0b2658e9__ 
__obfs_0731460__ __obfs_9059__ __obfs_8d__ __obfs_ac5dab__ __obfs_0533a88__ 
__obfs_f39ae9ff3a81f499__ __obfs_cd14821dab__ __obfs_dc40b7120e__ __obfs_3fab5__ __obfs_90e13__ 
__obfs_7ffd85d93__ __obfs_d1e946f4e67db__ __obfs_1f1baa5b8eda__ __obfs_39027dfad5138__ __obfs_64__ 
__obfs_6e79ed05baec2754__ __obfs_09b1__ __obfs_5b6ba13f79129__ __obfs_f542eae1949358e2__ __obfs_155fa0959__ 
__obfs_f0b__ __obfs_faa__ __obfs_f4a__ __obfs_f5c3dd7514bf__ __obfs_17c3433__ 
__obfs_f2__ __obfs_59___ __obfs_0e08__ __obfs_14__ __obfs_2647c1dba2__ 
__obfs_ed519dacc8__ __obfs_f442d33fa068320__ __obfs_fface8385abbf__ __obfs_4496bf24afe__ __obfs_aa2a7737137409__ 
__obfs_06___ __obfs_e0ab531ec3121__ __obfs_61b1fb3f59__ __obfs_9a1de__ __obfs_d757719ed7c2b66__ 
__obfs_dfce06__ __obfs_f26dab9bf__ __obfs_85f007f8c50dd__ __obfs_d7657583058__ __obfs_728f206c2a01b__ 
__obfs_201d728__ __obfs_e8dfff4__ __obfs_57c0531e13f4__ __obfs_4888241374e8c62__ __obfs_06a15eb1c38367__ 
__obfs_59____ __obfs_f45a1078feb35de__ __obfs_82cadb0649a3af4__ __obfs_7385db9a3f114__ __obfs_cd____ 
__obfs_8c__ __obfs_ff1418e8c__ __obfs_eb1e78__ __obfs_7503cfa__ __obfs_49ad__ 
__obfs_6ae07dcb33ec3b__ __obfs_3c947bc2f7__ __obfs_a3545bd79d31f9a__ __obfs_d7fd1__ __obfs_537de305e__ 
__obfs_96c5c28be__ __obfs_f9d__ __obfs_4e87337f366f7__ __obfs_09fb05__ __obfs_d0__ 
__obfs_69d__ __obfs_19de10adbaa1__ __obfs_a19acd7d2__ __obfs_c164bbc9d6c7__ __obfs_68c694__ 
__obfs_d305281faf947__ __obfs_fb8feff253bb6__ __obfs_2f25__ __obfs_d4b2ae__ __obfs_958adb57686__ 
__obfs_7e9e346dc5fd268__ __obfs_ba9a56ce0a9b__ __obfs_f31b20466ae89__ __obfs_dc5d637ed5e62c__ __obfs_44a2e08__ 
__obfs_3214a6d842cc__ __obfs_b4568df26__ __obfs_e1____ __obfs_c45__ __obfs_f0fcf351df4e__ 
__obfs_d5237__ __obfs_c366c2c9__ __obfs_7302e3f5e7c0__ __obfs_2d1b__ __obfs_6814859__ 
__obfs_865dfbde8a344b__ __obfs_1316__ __obfs_ca4__ __obfs_56f9f8__ __obfs_5fa9e41bfec0725__ 
__obfs_059fdcd96baeb7__ __obfs_e06f967fb0d3555__ __obfs_af33__ __obfs_11f__ __obfs_6be5336db2c11__ 
__obfs_9fdb__ __obfs_d54e99a6__ __obfs_fc4ddc15f9f4b4b__ __obfs_94462__ __obfs_c915__ 
__obfs_73e0f74__ __obfs_dea9ddb2__ __obfs_77369e37b2aa__ __obfs_65699726a3c601__ __obfs_0609154__ 
__obfs_ab7314__ __obfs_04df4d434d48__ __obfs_ff7d0f__ __obfs_c44__ __obfs_07a4e2__ 
__obfs_b432f34c__ __obfs_65fc52ed8f88__ __obfs_cb79f8fa58b91__ __obfs_e7___ __obfs_8c8a58fa97__ 
__obfs_44968aece94f667e__ __obfs_9f6992966__ __obfs_333222170ab9edc__ __obfs_414e773d5b7e5__ __obfs_b139e104214a0__ 
__obfs_0950ca92a4dcf4__ __obfs_5103c358__ __obfs_e5__ __obfs_5bce843d__ __obfs_139f0874f2ded__ 
__obfs_29530de21__ __obfs_15d185eaa__ __obfs_52d__ __obfs_1e913e1b06__ __obfs_8562ae5__ 
__obfs_8d55a249e6ba__ __obfs_11108a3db__ __obfs_13___ __obfs_ad4c__ __obfs_f22e4747da__ 
__obfs_95e68__ __obfs_7af__ __obfs_519__ __obfs_c3395dd46c34f__ __obfs_6f2688a5fce7d48c__ 
__obfs_2d00f43f07911355__ __obfs_1f71e393b380919__ __obfs_de03__ __obfs_7ca57a9f__ __obfs_36ac8e558ac769__ 
__obfs_03e7d2e__ __obfs_6a508a__ __obfs_111__ __obfs_a38b1__ __obfs_5a7f963e5e0504__ 
__obfs_378a0__ __obfs_e3__ __obfs_27___ __obfs_d77f0076__ __obfs_e4dd5528f759__ 
__obfs_7f16109f1619fd7__ __obfs_f106b7f99d2cb30__ __obfs_95f6870ff3dcd442__ __obfs_c215b44__ __obfs_39dca__ 
__obfs_d46__ __obfs_3683af9d6f6c__ __obfs_a82d922b133be19__ __obfs_98c724289__ __obfs_4d8556695c262a__ 
__obfs_0004d0b5__ __obfs_de7399880268__ __obfs_c4de8ced__ __obfs_deb54ffb__ __obfs_3d863__ 
__obfs_7d2b92b6726c__ __obfs_dd055f53a4570__ __obfs_4afd521d__ __obfs_405e289063__ __obfs_798cebccb3__ 
__obfs_f80bf05527157a8c__ __obfs_b3b4d2db__ __obfs_fb87582__ __obfs_1e4d36177d71b__ __obfs_1b3__ 
__obfs_1f36c15d6a3d1__ __obfs_8c___ __obfs_d68__ __obfs_9d7311b__ __obfs_4a3e00961a08879c__ 
__obfs_dc513ea4fbdaa7a1__ __obfs_960__ __obfs_d5c18698__ __obfs_c5a4e7e6882845e__ __obfs_008bd5ad93b754d5__ 
__obfs_3f088ebeda035__ __obfs_635__ __obfs_06964dce__ __obfs_c5b2c__ __obfs_5ec829d__ 
__obfs_08____ __obfs_d0fb96__ __obfs_4ba29__ __obfs_a59__ __obfs_b8b4__ 
__obfs_d4__ __obfs_ea5a486c71__ __obfs_a00e5eb097__ __obfs_ef8446f355__ __obfs_f1981e4bd8__ 
__obfs_d7a84628c02__ __obfs_c8758b51708__ __obfs_253614bb__ __obfs_8038__ __obfs_cee8d6b__ 
__obfs_65d2ea03425887a7__ __obfs_95192c9873238__ __obfs_8d8__ __obfs_84___ __obfs_ea6b2efbdd4255a9__ 
__obfs_7b7a53e239400a13__ __obfs_05a5cf06982ba__ __obfs_3a824154__ __obfs_5531a58348__ __obfs_07811dc6c422__ 
__obfs_312__ __obfs_c92a1032__ __obfs_9f62b8625f914a0__ __obfs_d860edd1dd83b3__ __obfs_093b60fd0557__ 
__obfs_2d579__ __obfs_88ef51f0__ __obfs_5352696a9ca3__ __obfs_a5a6171__ __obfs_d198bd736a97e7c__ 
__obfs_2b0f658cbf__ __obfs_f48c04ffa__ __obfs_23d2e1578544b1__ __obfs_2557911c1__ __obfs_a48564053b3c7b54__ 
__obfs_4c144c47ec__ __obfs_89885ff2__ __obfs_71e09b16e21f7b6__ __obfs_d79c__ __obfs_d8330f857a1__ 
__obfs_0189caa5525__ __obfs_38751__ __obfs_a501bebf79__ __obfs_051928341__ __obfs_06b1338ba02add__ 
__obfs_aebf7782a3d445__ __obfs_a9813e9550fe__ __obfs_584b98aac2ddd__ __obfs_f3e52c300b822__ __obfs_955c__ 
__obfs_9a___ __obfs_a96d3afec__ __obfs_df4fe__ __obfs_1359aa93__ __obfs_2eace51d__ 
__obfs_f8c0c96863284__ __obfs_52dbb0686f8bd0c__ __obfs_2d405b367158e3__ __obfs_16ba72172__ __obfs_f8bf09__ 
__obfs_0ae3f79a302__ __obfs_6f492___ __obfs_b5f1e8fb36cd7fbe__ __obfs_814a9c1__ __obfs_325995af77a0e8b0__ 
__obfs_296472c9542ad__ __obfs_fb2e203__ __obfs_07cb5f86508f146__ __obfs_4b86abe48d3__ __obfs_1f4fe6a4411__ 
__obfs_cbef4632102__ __obfs_6492d3__ __obfs_819e3d6__ __obfs_f4105__ __obfs_654ad60__ 
__obfs_54ff9e__ __obfs_0070d23__ __obfs_850af92f__ __obfs_3e9e39fed3__ __obfs_a0__ 
__obfs_e0a209__ __obfs_f80ff32e08a25270__ __obfs_4d6b3e38b9526002__ __obfs_d3a7__ __obfs_bf424cb7b0dea0__ 
__obfs_26f5b__ __obfs_0b1ec366924b26f__ __obfs_801__ __obfs_b2ab001909a8a6f0__ __obfs_cf2226ddd41b1a2d__ 
__obfs_2c__ __obfs_194cf6c2de8e0__ __obfs_a03fa30821986df__ __obfs_a1d7311f2a__ __obfs_978d76676f__ 
__obfs_2cad8fa47bbef__ __obfs_c586__ __obfs_8232e119d8f59aa8__ __obfs_7b__ __obfs_e7e23__ 
__obfs_24f0d2c__ __obfs_c6335734d__ __obfs_9185f3ec5__ __obfs_931af58__ __obfs_05546b0e38__ 
__obfs_c353__ __obfs_1a0a283b__ __obfs_a2___ __obfs_01931a69__ __obfs_51174add1__ 
__obfs_bdc4626aa1d1__ __obfs_4ba__ __obfs_3937230de3c8041__ __obfs_92b__ __obfs_1b5230e3ea6d__ 
__obfs_44cd7a8f7f9f851__ __obfs_02b1__ __obfs_abdbeb4d__ __obfs_5a1e3__ __obfs_ef41d488755367__ 
__obfs_a012869311d64a__ __obfs_3b92d__ __obfs_5227b6__ __obfs_bd5af7cd9__ __obfs_cd4bb35c__ 
__obfs_f15d337c7__ __obfs_a869ccbcbd9568__ __obfs_f6e79__ __obfs_c902b497eb972__ __obfs_fca0789e__ 
__obfs_9a49a25d845a4__ __obfs_4e6__ __obfs_9bb6dee__ __obfs_19____ __obfs_37d0__ 
__obfs_23c97e9cb93576e4__ __obfs_5d6646aad9bcc0be__ __obfs_2a34a__ __obfs_9f44e95__ __obfs_7dc1c76__ 
__obfs_c182f930a__ __obfs_936a40b7e8ee__ __obfs_0d73a25092e5__ __obfs_e21e4e58ad9ab5__ __obfs_d3096__ 
__obfs_24917db15c__ __obfs_350db0__ __obfs_a486cd__ __obfs_cb8__ __obfs_1e8c391a__ 
__obfs_a381c2c35c9157f__ __obfs_ee26fc6__ __obfs_d542599794c1c__ __obfs_697e382cfd__ __obfs_ddd9dda6bfaf__ 
__obfs_1819__ __obfs_33___ __obfs_86e78499ee__ __obfs_6e5025cc__ __obfs_c3e403__ 
__obfs_8929c70f8d710e41__ __obfs_32e0561__ __obfs_2596a54cdbb555c__ __obfs_41e76__ __obfs_bd0cc810b580__ 
__obfs_88a839f2f__ __obfs_f8e59f4__ __obfs_9978b7063e297d8__ __obfs_7bc__ __obfs_d1a21da__ 
__obfs_211c1e0b83b9c__ __obfs_0234c510bc6d9__ __obfs_bb1662b7c5f22a0__ __obfs_169779d3852b__ __obfs_12b1e42dc074__ 
__obfs_3a1dd983__ __obfs_100d9f30ca54b1__ __obfs_d51b__ __obfs_2056d__ __obfs_00a03ec65__ 
__obfs_f1__ __obfs_81b3833e2__ __obfs_e2ad76f2326__ __obfs_b440509a0106086a__ __obfs_1c6a0198177bfc__ 
__obfs_0a87257e53__ __obfs_71560ce98c82__ __obfs_14ea0d5b0c__ __obfs_ca___ __obfs_cdf1e288ca02__ 
__obfs_8c5f6ecd__ __obfs_25__ __obfs_ea119a40__ __obfs_6832a7b24b__ __obfs_1145a30ff80__ 
__obfs_5249__ __obfs_e45823af__ __obfs_dd28e506350__ __obfs_2d969e__ __obfs_4b4edc2630fe__ 
__obfs_06d5ae105__ __obfs_fea9__ __obfs_4aecfbe5__ __obfs_cd3afef9__ __obfs_db11__ 
__obfs_1368ba1ab6ed38__ __obfs_3323fe11e9595c09__ __obfs_05a70454516__ __obfs_01894d6f048__ __obfs_f3d9de86462__ 
__obfs_02e656ade__ __obfs_5938b4d0__ __obfs_b5c01503041b7__ __obfs_b0df2270be9cb16c__ __obfs_13111c20ae__ 
__obfs_d2a27e83d4__ __obfs_598920e1__ __obfs_934b535800__ __obfs_04048aeca2c0__ __obfs_8ca8da41__ 
__obfs_443de__ __obfs_01eee509ee2f68dc__ __obfs_efdf562ce2fb0ad4__ __obfs_4ae67__ __obfs_6cd9313ed34__ 
__obfs_32__ __obfs_2a8a812400df89__ __obfs_3e626__ __obfs_e0f7a4d0ef9b84b__ __obfs_653a__ 
__obfs_b0b79da57b95__ __obfs_3dd9424__ __obfs_b166b57d1__ __obfs_29523510979__ __obfs_487d4__ 
__obfs_d4dd1__ __obfs_b6e3__ __obfs_1a3f91fead97497b__ __obfs_90aef9__ __obfs_3147da8ab4a__ 
__obfs_109__ __obfs_758a06618c69880__ __obfs_df1f1d20ee8670__ __obfs_be6__ __obfs_243f__ 
__obfs_a07c2f3b3b__ __obfs_d5e2c0adad503c91__ __obfs_6354__ __obfs_ce6c92303f38__ __obfs_38651c4450f873__ 
__obfs_c2ba1bc54b239__ __obfs_f6c79f4af47863__ __obfs_d6__ __obfs_2d__ __obfs_04ad563202__ 
__obfs_4cb811134b9d39f__ __obfs_bbaa9d6a1445__ __obfs_0233f3b__ __obfs_26505e0__ __obfs_ccbd8ca962__ 
__obfs_66e8ba821__ __obfs_eb76c035d5__ __obfs_53___ __obfs_2b8eba3cb0d0f__ __obfs_51de85ddd068f0b__ 
__obfs_cd0f7__ __obfs_a376033f78e14__ __obfs_743394b__ __obfs_074177d3eb__ __obfs_95f8d9901ca887__ 
__obfs_cd0cbcc668fe4bc__ __obfs_6150ccc606__ __obfs_fe40fb9__ __obfs_cc7e2b878868c__ __obfs_9667150__ 
__obfs_dc16622ddc767e__ __obfs_0f46c64b7__ __obfs_d6bcb486f7__ __obfs_716e1b8c6cd17b77__ __obfs_80537a945c7aaa78__ 
__obfs_ae1eaa32d10b6c88__ __obfs_fa243__ __obfs_5b8e4fd39d97862__ __obfs_c36__ __obfs_43351f7bf9a215__ 
__obfs_1177__ __obfs_98e6f1720902__ __obfs_478__ __obfs_5f6371c9__ __obfs_229754d77991__ 
__obfs_16026d6__ __obfs_130f1a8e9__ __obfs_e069ea__ __obfs_3de568f8__ __obfs_40b5f25a22857__ 
__obfs_46a558d97__ __obfs_2b45c629e57__ __obfs_ffedf5be__ __obfs_d827f12e3__ __obfs_e6c2dc3dee4__ 
__obfs_2d2__ __obfs_f976__ __obfs_6211080fa89__ __obfs_e58aea6__ __obfs_f516dfb84b9__ 
__obfs_49c0b9d84c2a16f__ __obfs_046ddf96__ __obfs_69dafe8b580664__ __obfs_f3ac63c91272__ __obfs_db9e__ 
__obfs_88bfc__ __obfs_778609db5dc7e1a__ __obfs_68d30981254__ __obfs_426f99__ __obfs_a11f__ 
__obfs_a70dc40__ __obfs_761c7920f470038d__ __obfs_228b__ __obfs_1498__ __obfs_d5e__ 
__obfs_6c97cd07663b0__ __obfs_f1e__ __obfs_03255088ed6335__ __obfs_fd69dbe2__ __obfs_be53d253d6bc__ 
__obfs_619205da514e83f__ __obfs_273448411d__ __obfs_e77dbaf67__ __obfs_f7__ __obfs_7e3b7a5bafcb0f__ 
__obfs_7b4773c0__ __obfs_a3eb043e7__ __obfs_806fec5af__ __obfs_b6cda1__ __obfs_359__ 
__obfs_43e4e6a6f341e006__ __obfs_c8dfece5cc682492__ __obfs_2321994d85__ __obfs_7cc532d783a7__ __obfs_f52854__ 
__obfs_81b073__ __obfs_777669af68dbcc__ __obfs_b2397517665__ __obfs_20c9f__ __obfs_70fcb77e63__ 
__obfs_326a8c055c0__ __obfs_0abdc563a06__ __obfs_92049d__ __obfs_23af4__ __obfs_d254c8a0__ 
__obfs_3f53d7190148675__ __obfs_ea204361__ __obfs_d095a94d20dc__ __obfs_d20be76a86c0d__ __obfs_d6911__ 
__obfs_4ebd440d99504__ __obfs_794288f252f45__ __obfs_8aec5__ __obfs_505259__ __obfs_f7e2b2b75b041756__ 
__obfs_9fb__ __obfs_d3b__ __obfs_300891a621__ __obfs_466accbac9a66b__ __obfs_ab8aa05e78248__ 
__obfs_ca43108ded__ __obfs_0a65e19__ __obfs_4c5bcfec__ __obfs_5f146156__ __obfs_8cbd005a556cc__ 
__obfs_123b7f02433572__ __obfs_6ee69d3769__ __obfs_269d83__ __obfs_3837a451cd0a__ __obfs_add217938e07__ 
__obfs_da4902cb0b__ __obfs_7b66b4f__ __obfs_ee8fe9093f__ __obfs_3ba__ __obfs_ea159dc978__ 
__obfs_1a6__ __obfs_99f59c0842e83c8__ __obfs_8b4224068a41c__ __obfs_d04863f100d__ __obfs_063e26c670d07bb__ 
__obfs_999600eb275cc__ __obfs_10__ __obfs_a554f__ __obfs_52cf49fea5ff6658__ __obfs_d0921d442ee91b__ 
__obfs_b0904096885__ __obfs_dcf6070a4ab__ __obfs_878d5691__ __obfs_565030e1fce4e481__ __obfs_bc7f62145__ 
__obfs_03cf87174debac__ __obfs_959ef477__ __obfs_4dd__ __obfs_bd7db7397f__ __obfs_8208974663db__ 
__obfs_b53477c2__ __obfs_de7092ba6df4276__ __obfs_97416ac0__ __obfs_7cac11e2f46ed46__ __obfs_b3f61131__ 
__obfs_a6__ __obfs_ddeebdeefdb7e7e__ __obfs_18___ __obfs_72e6d32__ __obfs_cb2c2041d97__ 
__obfs_e3ca0449fa__ __obfs_5dec7070__ __obfs_ac1ad983e08ad330__ __obfs_db60b9__ __obfs_020bf2c45e7bb322__ 
__obfs_7993e11204b215b2__ __obfs_e139c454239bfd__ __obfs_be1df9a5d087249__ __obfs_af5d5ef24__ __obfs_4a06d868d__ 
__obfs_f836305__ __obfs_c65d7bd70fe3e5e__ __obfs_2aaa__ __obfs_cc0991344c3d760__ __obfs_a9365bd906e1132__ 
__obfs_1f__ __obfs_cbf871__ __obfs_d16509f6eaca102__ __obfs_0fe473396__ __obfs_f708f0__ 
__obfs_b1301141f__ __obfs_5314b9674c86e3f__ __obfs_6547__ __obfs_3cf2559725a9f__ __obfs_fc79250f8c5__ 
__obfs_feecee9__ __obfs_7a68443__ __obfs_6048ff4e8cb07aa6__ __obfs_24e27b869b66e9__ __obfs_7f__ 
__obfs_9ed9328611fe3f45__ __obfs_2f4fe03d777__ __obfs_2c3ddf4__ __obfs_07a9d3fe__ __obfs_61d77652c97ef__ 
__obfs_49d4b2fa__ __obfs_2dbf2163__ __obfs_28b__ __obfs_8c9f32e03aeb2e__ __obfs_03__ 
__obfs_b427426b8acd__ __obfs_7cf64379eb6f29__ __obfs_7e____ __obfs_54b2b21af__ __obfs_8bdb5058__ 
__obfs_e9412ee56438__ __obfs_cf05968255451bde__ __obfs_10c66082c1__ __obfs_1843e35d41c__ __obfs_70c445ee64b1__ 
__obfs_1e0a84051e6a4a73__ __obfs_7b___ __obfs_250413d2__ __obfs_e82c4__ __obfs_57bafb2c2dfeefba__ 
__obfs_7cc234202e9__ __obfs_d9ff90f4__ __obfs_73f490f3f868__ __obfs_5e6bd7a69__ __obfs_0bf727e907c5__ 
__obfs_fec87a37c__ __obfs_c8067ad193__ __obfs_4c8c76b39__ __obfs_53f__ __obfs_1f34004ebcb05__ 
__obfs_b06b5541a__ __obfs_6b5754d__ __obfs_f5__ __obfs_2c6ae45a3e88aee__ __obfs_b4baaff0e2__ 
__obfs_ea4eb4__ __obfs_bb03__ __obfs_6a4c__ __obfs_7989eda__ __obfs_34__ 
__obfs_347665597cb__ __obfs_01a068__ __obfs_46515dc__ __obfs_8a20a8621978__ __obfs_c30fb4dc55d801__ 
__obfs_33bb8__ __obfs_12ffb096__ __obfs_d9f__ __obfs_9af76329c78__ __obfs_cd10c7f37618__ 
__obfs_f7696a9b36__ __obfs_3f998e713a6e__ __obfs_696b35cc35e__ __obfs_e7____ __obfs_7884a9652e__ 
__obfs_8c1b6fa97c4288a__ __obfs_87682805257e__ __obfs_836__ __obfs_30aaf34d6afd4b__ __obfs_8db9264228dc48f__ 
__obfs_4e02__ __obfs_f8b932c70d0b2e6b__ __obfs_831caa1b__ __obfs_84b20b1f5a__ __obfs_b06f50d1f89bd8__ 
__obfs_415e1af7ea95f8__ __obfs_8d09e4b85c783c__ __obfs_c5d__ __obfs_6ef80__ __obfs_4a8423d5e91fd__ 
__obfs_070dbb6024b5ef__ __obfs_4a1590df1__ __obfs_0d7__ __obfs_a6___ __obfs_31c__ 
__obfs_9407c82__ __obfs_23__ __obfs_ba3e9b6a51__ __obfs_6be93f7a__ __obfs_82ca5dd156__ 
__obfs_55a988d__ __obfs_217c__ __obfs_9824f9c__ __obfs_4de75__ __obfs_7827d__ 
__obfs_0747b9be4f9__ __obfs_f7a__ __obfs_40__ __obfs_1bf0c59238dd24__ __obfs_2aedcba6__ 
__obfs_9657__ __obfs_e92d74ccacdc984__ __obfs_c3a690be93__ __obfs_1b1132__ __obfs_f0__ 
__obfs_9d28de8ff9__ __obfs_92a0e__ __obfs_86ecf__ __obfs_0e4a2c65bdad__ __obfs_b21f9f98829dea9a__ 
__obfs_8535__ __obfs_921c2dc40d0__ __obfs_4be5a36cbaca8a__ __obfs_d7619beb6eb18__ __obfs_8c59__ 
__obfs_5acdc9ca5d99ae6__ __obfs_1d94108e907bb8__ __obfs_16808__ __obfs_2288f691__ __obfs_b5baa9c__ 
__obfs_eb___ __obfs_59eb5dd36914c2__ __obfs_dbab2adc8f9d__ __obfs_dbd22__ __obfs_8169__ 
__obfs_e6acf4b0f69f6f6e__ __obfs_42fe880812__ __obfs_dda04f9d6341__ __obfs_48c3e__ __obfs_02f657d55e__ 
__obfs_852c44ddc__ __obfs_283085d30e105__ __obfs_c0e905__ __obfs_60519c3dd2__ __obfs_8f___ 
__obfs_fecf__ __obfs_ef1e491a7__ __obfs_74__ __obfs_9457__ __obfs_5b168fdba5ee5ea2__ 
__obfs_17b3c70617__ __obfs_309a8e73b__ __obfs_7e83722522e8aeb__ __obfs_eaa52f3366768bc__ __obfs_92426b262d11b0ad__ 
__obfs_36__ __obfs_c57168a952__ __obfs_ef0__ __obfs_fb89fd138b10__ __obfs_743c41__ 
__obfs_7876acb__ __obfs_978f__ __obfs_18bb68e2b38e4__ __obfs_026a39ae63343c__ __obfs_ce75840__ 
__obfs_453fad__ __obfs_bd70364a8fc__ __obfs_ed578__ __obfs_4ebc__ __obfs_50abc3e730e36b3__ 
__obfs_32b___ __obfs_e02e__ __obfs_6403675579f61145__ __obfs_92f54963fc39__ __obfs_880610a__ 
__obfs_d3fad7d3634__ __obfs_a431d70133ef__ __obfs_53c6de78244e9f__ __obfs_d756d3d2b9dac7__ __obfs_339a18def9898dd__ 
__obfs_8dc5983b8c4ef1d8__ __obfs_321cf86b4c9f__ __obfs_1175defd0__ __obfs_6aed000af__ __obfs_5df07ec__ 
__obfs_c4f796af__ __obfs_a3d06db1f8c85b__ __obfs_75e33da9b__ __obfs_17f98ddf04__ __obfs_40173ea48d__ 
__obfs_8bd__ __obfs_cc7090__ __obfs_06fe1c234519f6__ __obfs_8e68c3c7bf1__ __obfs_f1748d6b0fd9__ 
__obfs_6412fef87392ae8c__ __obfs_e354fd90__ __obfs_4de81d910__ __obfs_8e065119c74efe3__ __obfs_8cff9bf6694dcc__ 
__obfs_dd__ __obfs_e113bb92c6939__ __obfs_75__ __obfs_fc03d482532__ __obfs_b75bd27b5a4__ 
__obfs_ed277964__ __obfs_c61fb__ __obfs_c60d__ __obfs_06c284d3__ __obfs_09a5e2a11b__ 
__obfs_9a5748a2__ __obfs_f21e__ __obfs_f12f2b34a0c31742__ __obfs_38181d9__ __obfs_f35a__ 
__obfs_a7789e__ __obfs_f2___ __obfs_0b7e926154c12__ __obfs_eb06b9db06012a__ __obfs_30f8f6b940d1073__ 
__obfs_d8bf84__ __obfs_148260a1ce4fe4__ __obfs_0c215f1942760__ __obfs_217e34__ __obfs_7180cffd6a8e82__ 
__obfs_e0688d139__ __obfs_1680e9fa7b__ __obfs_b096577e26__ __obfs_18ad989__ __obfs_358a__ 
__obfs_1b9__ __obfs_2417dc8af8570f__ __obfs_98b418276d571e62__ __obfs_90__ __obfs_daaaf13651380465__ 
__obfs_e727f__ __obfs_1102a326d5f7c__ __obfs_7edccc6614__ __obfs_5ac8bb8a7d7__ __obfs_0bed45bd5__ 
__obfs_028ee724157b05d0__ __obfs_f8___ __obfs_0e900ad84f63__ __obfs_88___ __obfs_a8__ 
__obfs_a8___ __obfs_d89a__ __obfs_e97c864e8ac__ __obfs_94aef38441e__ __obfs_98___ 
__obfs_220a7f__ __obfs_dcda54__ __obfs_f1___ __obfs_84____ __obfs_7c4bf50b71550__ 
__obfs_41ab1b__ __obfs_3a0844cee4fc__ __obfs_573__ __obfs_b3__ __obfs_577fd60255d4bb0f__ 
__obfs_f6185f0ef0__ __obfs_110eec23201__ __obfs_d790c9e6c0b5e02__ __obfs_3bd401731__ __obfs_cf9b2d__ 
__obfs_dbbf603ff0__ __obfs_dc2b690516158a87__ __obfs_ab452534__ __obfs_fb4ab556bc42__ __obfs_04__ 
__obfs_f1____ __obfs_df0e0__ __obfs_2e7ceec8361275c4__ __obfs_220c77af02f__ __obfs_81c2f886f91e18f__ 
__obfs_82___ __obfs_2e7__ __obfs_65f2a94c8c2d56d5__ __obfs_03fa2f7502f5f6__ __obfs_5a99__ 
__obfs_de594__ __obfs_65fc__ __obfs_bbeb0c1b1fd__ __obfs_403ea2e__ __obfs_b628386c9b924__ 
__obfs_ff2c__ __obfs_cdd96e__ __obfs_058d6f2fb__ __obfs_ad47a008a2f806a__ __obfs_7aee26__ 
__obfs_fa2e8c438__ __obfs_362387__ __obfs_33267e5__ __obfs_c315f0320b7cd4ec__ __obfs_64a08e5f1e6c39fa__ 
__obfs_4bbdcc0e82__ __obfs_b1c00bcd4__ __obfs_23fc4cb__ __obfs_5e751896e527c86__ __obfs_b7f1f29db7c2364__ 
__obfs_421b3ac5__ __obfs_08f38e043__ __obfs_3614__ __obfs_ec1f850d934f4__ __obfs_7f7c351ee__ 
__obfs_1d497__ __obfs_47fd3c87f42f55d__ __obfs_9ff7c9eb9d37f43__ __obfs_a4613e8d72__ __obfs_5658__ 
__obfs_96f2b50__ __obfs_cdcb2f__ __obfs_78f7d96ea21cca__ __obfs_22b1f2e__ __obfs_5a45828dead__ 
__obfs_531db99c__ __obfs_d37124c4c__ __obfs_868b__ __obfs_1006ff__ __obfs_d37b3ca__ 
__obfs_fc192b0c0d270db__ __obfs_030e65da2b1__ __obfs_b2ea5e977c5fc__ __obfs_9dc372713683fd8__ __obfs_04___ 
__obfs_1769__ __obfs_9a11883317fde__ __obfs_d58e2__ __obfs_7f1___ __obfs_35c5__ 
__obfs_b0be__ __obfs_566a9968b436285__ __obfs_2b692__ __obfs_f804d211__ __obfs_98d8a23f__ 
__obfs_370__ __obfs_045cf83ab07__ __obfs_f75526659f310__ __obfs_f499d34bd87b4__ __obfs_44ac09ac6a14913__ 
__obfs_a7a3d7__ __obfs_d8e1344e27a5b08__ __obfs_92bf5e6240__ __obfs_f565bb9e__ __obfs_1cd138d0499a68__ 
__obfs_4a5876b450b453__ __obfs_6244b2ba9__ __obfs_b4a721cfb62f5__ __obfs_fd4f21f2556d__ __obfs_b1300291698eade__ 
__obfs_d478446__ __obfs_ae587cfeea5ac21a__ __obfs_60243__ __obfs_ccd__ __obfs_ae__ 
__obfs_5be278a9e02bed__ __obfs_fb3f76858cb38__ __obfs_2e0bff759d057e__ __obfs_d210cf373__ __obfs_b19aa25ff__ 
__obfs_ec__ __obfs_ad82140cafe81__ __obfs_12__ __obfs_4191ef5f6c__ __obfs_e465ae46b0705__ 
__obfs_a7f592cef__ __obfs_e27a949795bbe863__ __obfs_74378__ __obfs_952c3ff98a__ __obfs_0d9095b__ 
__obfs_0fc170ecbb8ff__ __obfs_a3788c8c64fd6__ __obfs_2eb5657d37f474e__ __obfs_64c318216__ __obfs_4ab52371762__ 
__obfs_564645fb__ __obfs_c0f971d8__ __obfs_765d5fb115a__ __obfs_d00__ __obfs_b4fd1d2cb085390__ 
__obfs_66__ __obfs_227f6afd3b7f__ __obfs_f3b7e5d3e__ __obfs_39d3__ __obfs_8e9__ 
__obfs_f5b1b89d98b__ __obfs_4e2a__ __obfs_18____ __obfs_d53697441ef12__ __obfs_28acfe2da49__ 
__obfs_aee92f16efd522__ __obfs_56cb94cb34617__ __obfs_0172d2__ __obfs_46f76a4bda9a9579__ __obfs_b030afbb__ 
__obfs_3fc2c__ __obfs_12311d05c9aa__ __obfs_09b69adcd7cbae__ __obfs_b1____ __obfs_46b2644cbdf489fa__ 
__obfs_07380__ __obfs_4ea__ __obfs_2bc8ae25856bc__ __obfs_ade5540__ __obfs_9752d873fa71c19__ 
__obfs_6775a0635c30__ __obfs_6e0e24295e8a__ __obfs_353de__ __obfs_d0bb8259__ __obfs_5d75b9__ 
__obfs_a78482ce76496f__ __obfs_d71fa38b648d__ __obfs_381__ __obfs_bf2fb7d1825a1df3__ __obfs_6f1d0705__ 
__obfs_4b29__ __obfs_eb9fc349601c6__ __obfs_fdf1bc5669e8f__ __obfs_5a2756a3cb9c__ __obfs_221__ 
__obfs_e833e042f5__ __obfs_d3d80b656929a__ __obfs_881c6e__ __obfs_d3aeec875__ __obfs_3070e6addcd702cb__ 
__obfs_1a6727__ __obfs_139738__ __obfs_449__ __obfs_42a6845a557be__ __obfs_a226e450e214f__ 
__obfs_894db62f7b7a6ed__ __obfs_bd135462__ __obfs_1ec3e7af38e__ __obfs_e6cbc650cd57__ __obfs_ef0d17b3bdb4__ 
__obfs_85690f81aadc1749__ __obfs_80__ __obfs_1a99f6__ __obfs_8b3bac1__ __obfs_e2c6__ 
__obfs_327708d__ __obfs_2650d6089a6d6__ __obfs_7e0a020__ __obfs_efd7e9ed0e5e694__ __obfs_e6af4__ 
__obfs_4f1f29888cabf5d4__ __obfs_12a1d073d5__ __obfs_f076073__ __obfs_a6db4ed04f162__ __obfs_ec8b57b__ 
__obfs_c61f571dbd2fb949__ __obfs_445__ __obfs_2ef35a8b78b5__ __obfs_c30__ __obfs_780965ae22ea6ae__ 
__obfs_e98741479a7b__ __obfs_15cf76466b972647__ __obfs_1dba__ __obfs_488c1e03__ __obfs_7f018eb7b301a666__ 
__obfs_b4944963b5c83d54__ __obfs_7a006957be65__ __obfs_6fe13__ __obfs_9719a00ed0c5709d__ __obfs_5b413__ 
__obfs_6b8b__ __obfs_e8f2779682__ __obfs_6e3197aae9__ __obfs_25ef0d887bc__ __obfs_332647f433a1__ 
__obfs_f9fd2624bee__ __obfs_a57e8915461b83a__ __obfs_379a7ba015d8bf1c__ __obfs_3c333aadfc3ee8e__ __obfs_b8b9c74ac__ 
__obfs_3144__ __obfs_9e82757e9a1c__ __obfs_c7558e9d1f956b01__ __obfs_73b8170__ __obfs_b5__ 
__obfs_dba31bb5c7599__ __obfs_ef67f7c2d86__ __obfs_c68c9c8258ea7d85__ __obfs_b31df__ __obfs_17eb7ecc__ 
__obfs_e924517087669__ __obfs_340a3904__ __obfs_dfb84a11f431c__ __obfs_f6c9dc70ecfd8__ __obfs_6271faad__ 
__obfs_465636eb4a7__ __obfs_17____ __obfs_6d19c113404ce__ __obfs_a4666cd9e1ab0e4__ __obfs_39536__ 
__obfs_ac34ae1fda29b8fe__ __obfs_56c82ccd658e__ __obfs_2b64__ __obfs_90___ __obfs_a36b0dcd1e__ 
__obfs_6624b__ __obfs_86c4a__ __obfs_c4294__ __obfs_25766f01__ __obfs_5dc126b503__ 
__obfs_b6617980ce__ __obfs_ec7f346604f__ __obfs_8fc__ __obfs_42853a61b26__ __obfs_6c9__ 
__obfs_8e9304__ __obfs_4b21cf96d4cf__ __obfs_2a0f97f81755__ __obfs_6e__ __obfs_0c1c995b77ea__ 
__obfs_892c3b1c6dccd5__ __obfs_c9efe5f2__ __obfs_ad8e88__ __obfs_15___ __obfs_e07bceab69529__ 
__obfs_bc4e356fe__ __obfs_02180771a__ __obfs_1b79b52d1bf__ __obfs_e2f9247929b__ __obfs_dc20d1211__ 
__obfs_b4__ __obfs_db5cea26__ __obfs_e2___ __obfs_b91b1facf3__ __obfs_779efbd24d5a7e3__ 
__obfs_d1c37__ __obfs_3e60e09c222f206c__ __obfs_3b2d8f129ae2f408__ __obfs_b887d8__ __obfs_60ad838__ 
__obfs_1c303b0e__ __obfs_65a31da7ede4dc9__ __obfs_63f446__ __obfs_62da8c91ce__ __obfs_466473650__ 
__obfs_6db291ac__ __obfs_af44c4__ __obfs_0f21f0349__ __obfs_e3___ __obfs_6788076842__ 
__obfs_2e__ __obfs_a2____ __obfs_2bd2e33__ __obfs_9edcc1391c208ba0__ __obfs_2d71b2ae158c7c59__ 
__obfs_aa6b7a__ __obfs_9ff0525c64bf3d4__ __obfs_a11ce019e96a4c6__ __obfs_b1b04__ __obfs_1c___ 
__obfs_275d7fb__ __obfs_769675d7c11f33__ __obfs_ae1d2c2d__ __obfs_faa453efd__ __obfs_5848ad959__ 
__obfs_f6b5f8c32c6__ __obfs_c5c1c__ __obfs_24b__ __obfs_58aa__ __obfs_ec47a5de1eb__ 
__obfs_cb12d__ __obfs_f404__ __obfs_a0b83c02d720__ __obfs_71887f__ __obfs_a36e841c5__ 
__obfs_e93028bdc1aacdf__ __obfs_908c9a56__ __obfs_d806ca13ca3449__ __obfs_a43__ __obfs_20479c788fb__ 
__obfs_3a61__ __obfs_5f268dfb__ __obfs_a72__ __obfs_c02f9de3c2f30__ __obfs_ee16f__ 
__obfs_22722a343513__ __obfs_b1f62fa99de9f27a__ __obfs_5a__ __obfs_41___ __obfs_77e__ 
__obfs_51be2fed6c55f__ __obfs_53a1320__ __obfs_248024541dbda1d__ __obfs_9a96a2c73c0d4__ __obfs_a74c3b__ 
__obfs_e4____ __obfs_9cb9ed4f35c__ __obfs_c8862fc1a3272571__ __obfs_09__ __obfs_e5___ 
__obfs_2bd235c31__ __obfs_0cdf61037d7053__ __obfs_b922ede9c__ __obfs_7edfd52220e__ __obfs_a0ba2648acd23dc7__ 
__obfs_2d95__ __obfs_0cd60efb__ __obfs_8a56257ea05c7401__ __obfs_272e11700558e2__ __obfs_7b6__ 
__obfs_03bfc1d478396__ __obfs_4b86ca4__ __obfs_10ce03a1ed01__ __obfs_a92c27__ __obfs_f0204e1d3ee3e4b0__ 
__obfs_9023e__ __obfs_9922f__ __obfs_3fd60983292458bf__ __obfs_fc325d4__ __obfs_b8af__ 
__obfs_0ebf197205c00fc__ __obfs_975e61077__ __obfs_8e489b4966fe8f7__ __obfs_5d___ __obfs_4fa177df228645__ 
__obfs_ef72d5__ __obfs_f0b1d5879866f2__ __obfs_c1__ __obfs_17754__ __obfs_d9b1655__ 
__obfs_2836be05e71a__ __obfs_dc6e224__ __obfs_c1502ae5a4d514b__ __obfs_3f5ee243547__ __obfs_cc431fd7__ 
__obfs_0a5c79b__ __obfs_4aa0e93b91__ __obfs_1aa057313c28fa4__ __obfs_1b__ __obfs_494b__ 
__obfs_6fec24eac__ __obfs_d8ab1a52f058358b__ __obfs_fed__ __obfs_f5496252609c43__ __obfs_bdb6920ad__ 
__obfs_bb073f2__ __obfs_6917ff2a7__ __obfs_be767243ca8f57__ __obfs_c8cd63e1bf13c501__ __obfs_639d79cc8__ 
__obfs_a2186aa7c__ __obfs_b6e710870acb__ __obfs_663fd3c5144fd10__ __obfs_1091660f3dff__ __obfs_f44ee263952e65__ 
__obfs_a9986c__ __obfs_ce60ff__ __obfs_f14bc21be7eaee__ __obfs_d3__ __obfs_1706f191d760c7__ 
__obfs_2bb0502c8__ __obfs_a081cab429ff7a3b__ __obfs_78bc62d08a9a0__ __obfs_dc6a7e__ __obfs_ccd2e3e__ 
__obfs_748d6b6ed8e__ __obfs_05b8caaf6__ __obfs_6a__ __obfs_8004d637b6236__ __obfs_512fc3c5__ 
__obfs_4db0f8b0fc8__ __obfs_60792d855cd8a9__ __obfs_3b502__ __obfs_ada5e0b63ef60e22__ __obfs_b23f5220__ 
__obfs_cc3d69ed781b16__ __obfs_62f91ce9b82__ __obfs_c5d9256689c4__ __obfs_96629f1aac6d__ __obfs_75b9b6dc7fe444__ 
__obfs_37e7897__ __obfs_4aec1b3__ __obfs_1cfead9959__ __obfs_ffbd6c__ __obfs_d4a897919a124958__ 
__obfs_e9f__ __obfs_9e6a921fbc42__ __obfs_87f4d79__ __obfs_532b7cbe070a357__ __obfs_bbb001ba009ed117__ 
__obfs_366f0bc7bd1d__ __obfs_58191d__ __obfs_8b___ __obfs_f0031__ __obfs_f42c7f9c8aea__ 
__obfs_f231f2107df__ __obfs_097e26b2__ __obfs_a2d__ __obfs_2e0a__ __obfs_7c78335a8924215__ 
__obfs_019f8b946__ __obfs_9f8684__ __obfs_ca1d3153a1c__ __obfs_dff8e9c2a__ __obfs_c6a01432c8138d__ 
__obfs_c922de9e__ __obfs_54fd__ __obfs_fb26__ __obfs_7221e5c8e__ __obfs_35937e3__ 
__obfs_8b83881__ __obfs_2ecd2bd94734e5d__ __obfs_8c9a__ __obfs_86b20716fbd5b253__ __obfs_e8bf0f27d70__ 
__obfs_747d344__ __obfs_92a08bf91__ __obfs_bd8528251__ __obfs_0afa92fc0f8a9cf0__ __obfs_a41b3bb3e6b05__ 
__obfs_1160453__ __obfs_5d4__ __obfs_38ed16__ __obfs_d8___ __obfs_32b3ee0272954__ 
__obfs_77ee3bc__ __obfs_98____ __obfs_32cbf687880eb1__ __obfs_9a____ __obfs_fdbd31f2027f2__ 
__obfs_b22b257ad05__ __obfs_2227d75__ __obfs_2b45e8d6abf590__ __obfs_55d99a37b2e__ __obfs_99ef04e__ 
__obfs_9808ae__ __obfs_29539ed932d3__ __obfs_d6___ __obfs_6a4d5952d4c__ __obfs_98b17f068d__ 
__obfs_b299ad86__ __obfs_5e6d27a7a8a8330d__ __obfs_20c86a628232a67__ __obfs_ce393994e8cf4308__ __obfs_7a98af17e__ 
__obfs_73e5080f0f3804__ __obfs_976abf__ __obfs_e25cfa90f043__ __obfs_e8258e5140317__ __obfs_45c__ 
__obfs_ce47be4abd__ __obfs_59dfa2df42d9e3d__ __obfs_d3630410c51e60__ __obfs_ba95d78a7c9425__ __obfs_91378b__ 
__obfs_c20a7ce2a627ba__ __obfs_f4aa__ __obfs_8051a3c405__ __obfs_d98961__ __obfs_3eb414bf1c2a66a__ 
__obfs_39ae2e__ __obfs_3f4__ __obfs_31c0__ __obfs_8d30aa96__ __obfs_8832ae391__ 
__obfs_07c4b1fdd1ef8d__ __obfs_f023559c6d59c0__ __obfs_766e428d1e23__ __obfs_68a9__ __obfs_563ca5e068b__ 
__obfs_7f01c939761597__ __obfs_6c4bb__ __obfs_721e7285__ __obfs_b08354f36__ __obfs_b59307fdacf7__ 
__obfs_731ae30af8750c2__ __obfs_24ec8468b67314c2__ __obfs_74___ __obfs_799de6d3dae4c__ __obfs_640258597__ 
__obfs_9ef2ed4b7fd2c__ __obfs_211ed78fe__ __obfs_d77e68596c__ __obfs_2ef248c04979__ __obfs_12___ 
__obfs_731309c4bb__ __obfs_6b620__ __obfs_0aae0f__ __obfs_9bd5ee6fe__ __obfs_89d4402dc03d3__ 
__obfs_e2ea__ __obfs_133b37__ __obfs_52edc__ __obfs_b016935__ __obfs_94b5bde6de888ddf__ 
__obfs_5812f92450cc__ __obfs_f5___ __obfs_687__ __obfs_df8397__ __obfs_0d352b4__ 
__obfs_6dfe08eda7__ __obfs_907edb0aa698622__ __obfs_aac61539fd1fb__ __obfs_040a99f2__ __obfs_85ae750ad1__ 
__obfs_c12706a__ __obfs_c3d377d10b13__ __obfs_12e0860668__ __obfs_b6d67__ __obfs_c5___ 
__obfs_f87522788a2be2d__ __obfs_ddcb155__ __obfs_544a__ __obfs_528aecdf9cf__ __obfs_ae35__ 
__obfs_d15426b9c324676__ __obfs_a64bd53139f71961__ __obfs_032__ __obfs_38811c5285__ __obfs_88e1__ 
__obfs_0e1e__ __obfs_d309cd6__ __obfs_ac4508__ __obfs_c57abe86de__ __obfs_06132__ 
__obfs_326fb04c3abf030__ __obfs_504c__ __obfs_1e3b21cb__ __obfs_4ad13f04ef4373__ __obfs_8deb8d1dd__ 
__obfs_2067e2650cd701__ __obfs_2131__ __obfs_4ea83d951990d8__ __obfs_485__ __obfs_a87d2__ 
__obfs_d54ce9de9df77c__ __obfs_951__ __obfs_8a50bae297__ __obfs_f8037f94e53__ __obfs_f0eaf5__ 
__obfs_f4334c131c781e2__ __obfs_ac730__ __obfs_073b0__ __obfs_a4d92e2cd5__ __obfs_c91e34__ 
__obfs_3f__ __obfs_bfbb56bee68d99af__ __obfs_79514e888b8f2ac__ __obfs_9c8661befa__ __obfs_2b323d6__ 
__obfs_52b738__ __obfs_b5___ __obfs_fd8c0__ __obfs_f507783927f2e__ __obfs_70___ 
__obfs_cc9657884708170__ __obfs_60a70bb05b08d6__ __obfs_a495e__ __obfs_c819904dde__ __obfs_c1d0f19c3f__ 
__obfs_72b386224056b__ __obfs_9ddb__ __obfs_946e3ece1fc8__ __obfs_b98249b38337c508__ __obfs_645e6bfdd05d1__ 
__obfs_3a3__ __obfs_980a875f__ __obfs_cfcce0621b49c98__ __obfs_ca3ec598__ __obfs_7a4303__ 
__obfs_d5d7f5bb__ __obfs_42cd6__ __obfs_7a4bf9ba2b__ __obfs_fa84632d7__ __obfs_737__ 
__obfs_63bfd6e8f26d1d3__ __obfs_8217bb4e7fa054__ __obfs_6fab6e3aa__ __obfs_f2____ __obfs_0e9d935f7e__ 
__obfs_b84__ __obfs_16fc18d7__ __obfs_d7aab42e6b8__ __obfs_c4b43ae017__ __obfs_2b7b82a7ec6de40__ 
__obfs_69386f6bb1d__ __obfs_bdd8817990ef209f__ __obfs_334467d41d5cf2__ __obfs_09___ __obfs_c46482d__ 
__obfs_62dad6e273d322__ __obfs_8ce5d989374d2__ __obfs_2c758__ __obfs_831b1ac5__ __obfs_8a1d694707__ 
__obfs_36ed197b3f31__ __obfs_3cfbdf46__ __obfs_f7cfdde9db36af8__ __obfs_a435__ __obfs_3ce6d3c__ 
__obfs_93682__ __obfs_dba132f6a__ __obfs_20b02dc951715__ __obfs_e94fe9a__ __obfs_ac8cd1808__ 
__obfs_29969626__ __obfs_0a2a51dac613882__ __obfs_b0ab42fcb71331__ __obfs_2be9bd__ __obfs_331316d4efb44__ 
__obfs_59a__ __obfs_98bd65207ee83bf__ __obfs_a4fa7175d4__ __obfs_2de7cf2__ __obfs_7ba06__ 
__obfs_f47122__ __obfs_acf06cdd9c74__ __obfs_14491b756__ __obfs_21c__ __obfs_3083__ 
__obfs_38a77aa456f__ __obfs_0655__ __obfs_1a04f96__ __obfs_333cb763f__ __obfs_69f268fb2ba__ 
__obfs_b7ee0d0d4__ __obfs_0b6ace9e897__ __obfs_0987b8b33__ __obfs_8b9e7ab295e8__ __obfs_d2cd33e9__ 
__obfs_ca793d8b79c1b66__ __obfs_a36b__ __obfs_0cd6a652__ __obfs_97108695bd93b6b__ __obfs_82b0639a82d0cc7__ 
__obfs_75df63609809c__ __obfs_8d9766a__ __obfs_39cd7b469beae7__ __obfs_664dd8__ __obfs_8a1ee9f2__ 
__obfs_b445e3141__ __obfs_07f75d9144912__ __obfs_0e7e05__ __obfs_165a59f7cf3b5c__ __obfs_dda99de58__ 
__obfs_900c563bfd2c48__ __obfs_285da2198b2b496c__ __obfs_37d0b499__ __obfs_0084ae4b__ __obfs_6c349__ 
__obfs_9b9b05072dd20d1__ __obfs_14___ __obfs_a9b4__ __obfs_2e___ __obfs_88855547570f7__ 
__obfs_f2bff080785c__ __obfs_6e16656a6ee1de72__ __obfs_29ddbd__ __obfs_0668e20b__ __obfs_2517756c5__ 
__obfs_131f383b43__ __obfs_31ca0ca71184bbd__ __obfs_4a11__ __obfs_62___ __obfs_8643c__ 
__obfs_8ed36a84__ __obfs_dbb422937d7f__ __obfs_6463c88460bd63bb__ __obfs_477b0__ __obfs_e8a642ed__ 
__obfs_82875__ __obfs_818de4d2ec21__ __obfs_5c80985bd40b8c__ __obfs_384babc3e7__ __obfs_57f04bb2975420__ 
__obfs_e945de21a1bb57__ __obfs_7fcc__ __obfs_91d0dbfd3__ __obfs_898dd88c__ __obfs_c6b8c8d762da__ 
__obfs_be1bc79__ __obfs_32fdab6559cdfa4__ __obfs_dab49080d80c7__ __obfs_73__ __obfs_20125fd__ 
__obfs_c6f798b__ __obfs_2fd0fd3efa7c4cf__ __obfs_90f1__ __obfs_30__ __obfs_63a7769efb__ 
__obfs_f6d9e4__ __obfs_1f___ __obfs_471c50ad1a1__ __obfs_d594b1a__ __obfs_4a53__ 
__obfs_643de__ __obfs_e846fb8a__ __obfs_73640de25b7__ __obfs_3d324c288__ __obfs_71a5c0514ab83__ 
__obfs_072__ __obfs_5d2c2cee__ __obfs_5421e013565f7f1__ __obfs_4500e4037738__ __obfs_caa__ 
__obfs_2d2c8394e31101a2__ __obfs_84c2d4860a0fc2__ __obfs_7200798__ __obfs_a91af177d301__ __obfs_14c879f3f5d__ 
__obfs_5b970a1d9b__ __obfs_61f2585b__ __obfs_c2f__ __obfs_f34185c4ca5d58e__ __obfs_4fa91c19016__ 
__obfs_7de3__ __obfs_b2004314__ __obfs_586f9b4035e599__ __obfs_12092__ __obfs_758be1f9f7__ 
__obfs_09ba3f0df1__ __obfs_5b4a214624__ __obfs_2e1b24__ __obfs_c5____ __obfs_86a1793__ 
__obfs_703__ __obfs_de7f47e09c8e05e6__ __obfs_66121d1f782d__ __obfs_f356355c163483__ __obfs_5abdf8b852__ 
__obfs_473447ac58e1__ __obfs_def7924e3199be5e__ __obfs_e1_____ __obfs_e3ea33961a7c__ __obfs_13d63838ef1fb__ 
__obfs_56503192b141__ __obfs_7e8d7e5__ __obfs_9edda0fd__ __obfs_73c0318__ __obfs_51e6__ 
__obfs_797134c3e4__ __obfs_606555__ __obfs_2a2717956118b__ __obfs_322f62469c5e__ __obfs_ca851e9f71b25d2__ 
__obfs_73fed7fd472e502d__ __obfs_735143e9__ __obfs_2974788b53f73e__ __obfs_99be__ __obfs_e91068fff3d7__ 
__obfs_d38ee1__ __obfs_dd___ __obfs_6d6968d87__ __obfs_b071c__ __obfs_6950aa0__ 
__obfs_e8e0d__ __obfs_3fb049__ __obfs_b7fe__ __obfs_cb953f6__ __obfs_966b6dfb__ 
__obfs_dfeb9598fbfb97__ __obfs_ab4f__ __obfs_944a5ae3483ed5c__ __obfs_c7b90b0fc2372__ __obfs_1b318124e37af6d__ 
__obfs_72f67e70f6b7cd__ __obfs_6c91724b8__ __obfs_0060e__ __obfs_ba036d228858d76f__ __obfs_6dbd2699e8e__ 
__obfs_84_____ __obfs_0a3__ __obfs_7535bbb91c8__ __obfs_fd9dcf1d14__ __obfs_3ea2db50e6__ 
__obfs_e2065cb56f55334__ __obfs_d4___ __obfs_d2350a54__ __obfs_87f__ __obfs_73231e__ 
__obfs_2a3d6__ __obfs_e0126439e08ddfbd__ __obfs_0e7__ __obfs_7d2be41b1bd__ __obfs_0141a8aedb1b53__ 
__obfs_15e122__ __obfs_9a85c12a21b7639__ __obfs_0dbb3fb9a__ __obfs_0f___ __obfs_7288251__ 
__obfs_5fef3e__ __obfs_cf1cf43cba274ae__ __obfs_b5b0db7f3a77ca4__ __obfs_5401acfe__ __obfs_1fd7b8__ 
__obfs_6c0958d82a83__ __obfs_98afdcc1ebd85da__ __obfs_ee14c41e92ec5c9__ __obfs_93931410__ __obfs_a9de093d__ 
__obfs_da9e6a4a4aeca9__ __obfs_0e4f5c__ __obfs_b87470__ __obfs_ead81fe8__ __obfs_9bdb8b1faffa4b__ 
__obfs_30a0b736094__ __obfs_e52ad5c9__ __obfs_afab3e97074__ __obfs_5a9d8bf5b7a4b35f__ __obfs_aa97d584861474f__ 
__obfs_b99d193b66a65429__ __obfs_291d43c696d8c370__ __obfs_416849da96fb7__ __obfs_1458e7509aa5f4__ __obfs_142c65e00f4f7cf__ 
__obfs_8844c5f0037__ __obfs_c5f5c23be__ __obfs_8487__ __obfs_196__ __obfs_147ebe637038ca5__ 
__obfs_06____ __obfs_a8166__ __obfs_e6ba70fc093b4c__ __obfs_50____ __obfs_db98dc0dbafde48__ 
__obfs_01__ __obfs_ab__ __obfs_7c220__ __obfs_e250c59336b505e__ __obfs_69b09198d4248__ 
__obfs_22b1cd16__ __obfs_656f0__ __obfs_51da85a3c3dfa1f__ __obfs_285a25__ __obfs_f11bec1411101c7__ 
__obfs_0ae1dd3__ __obfs_414a74971__ __obfs_ebf1__ __obfs_d04d42cdf14579__ __obfs_05edf455__ 
__obfs_e6e713296__ __obfs_6346dc72__ __obfs_dccab9bd9e__ __obfs_5481b2f__ __obfs_77c493ec14246__ 
__obfs_43b52842663fa6__ __obfs_f8f5161cf94d__ __obfs_842424a1d__ __obfs_8baca01b73__ __obfs_1b9f__ 
__obfs_c9f06bc__ __obfs_3f647__ __obfs_3e77a146297754__ __obfs_25___ __obfs_0d441de75945e5__ 
__obfs_630b7d8dd__ __obfs_6760__ __obfs_9d684c589d67031__ __obfs_69eba3__ __obfs_565767eb96d87__ 
__obfs_2668a710__ __obfs_224e5__ __obfs_aba53da__ __obfs_c2964caac096f__ __obfs_a38__ 
__obfs_da6ea7747__ __obfs_9001ca429212011__ __obfs_69f357fcc8e6d__ __obfs_cdd0__ __obfs_dce8af__ 
__obfs_c0____ __obfs_52c409f1571f5__ __obfs_b89c30965eb__ __obfs_6a450490f238b4d__ __obfs_e7e69cdf28f8c__ 
__obfs_8d762__ __obfs_62e7f2e__ __obfs_228b25587479f__ __obfs_6a8018b__ __obfs_c254e7753095807e__ 
__obfs_a05d8861__ __obfs_774b0e0775__ __obfs_967990de5b3ea__ __obfs_60a0575__ __obfs_649a0__ 
__obfs_f95ec__ __obfs_4c__ __obfs_d87ca511e2a8593c__ __obfs_c4fa7aeceda__ __obfs_6ad__ 
__obfs_d8c9d05ec6e__ __obfs_78d__ __obfs_db___ __obfs_4da9d7__ __obfs_820e694038__ 
__obfs_4baf54f36935058__ __obfs_c5b2__ __obfs_856b5__ __obfs_ecdcd675b3__ __obfs_5ee0070c4__ 
__obfs_dd7970532bfa__ __obfs_0ee8b85a85a49346__ __obfs_2bf283c0__ __obfs_3e524bf740__ __obfs_1305f6__ 
__obfs_1a551829d50f1400__ __obfs_fd4c2dc64ccb849__ __obfs_398475c83b47075e__ __obfs_acf9221__ __obfs_e2ea___ 
__obfs_a098b2eb313__ __obfs_48042b1dae4__ __obfs_cae82d435__ __obfs_895daa408f494a__ __obfs_ba304f3809ed__ 
__obfs_4f11b55f__ __obfs_22c5a901070d1__ __obfs_300d15__ __obfs_7ae11af20__ __obfs_8a05726__ 
__obfs_d0aa51__ __obfs_b5a1d925221__ __obfs_0d8080853a54__ __obfs_cff02a74da64__ __obfs_49c0__ 
__obfs_45ce__ __obfs_c203e__ __obfs_e1021d43911ca2c__ __obfs_2da6cc4a5d__ __obfs_cf88118aa2ba__ 
__obfs_310cc7ca5a76a446__ __obfs_14678db82874f1__ __obfs_a22d33b4a00c__ __obfs_30a237d18c50f563__ __obfs_0784__ 
__obfs_9627c45df__ __obfs_e761813f83dfc86f__ __obfs_2b346a0aa__ __obfs_ddf9029977a612__ __obfs_b67fb3360__ 
__obfs_6915849303a3fe9__ __obfs_1ea97de85eb__ __obfs_f095cedd__ __obfs_1d2a48c55f6f1__ __obfs_e1______ 
__obfs_77ec6f21c85b637__ __obfs_54__ __obfs_f3c89__ __obfs_740a02d__ __obfs_f35__ 
__obfs_845__ __obfs_113383__ __obfs_71d7232b9fed02__ __obfs_2151__ __obfs_74791__ 
__obfs_212__ __obfs_9426c311e76__ __obfs_89__ __obfs_acb5d11__ __obfs_c90e2__ 
__obfs_55__ __obfs_dc727151e5d55__ __obfs_6754e06e46__ __obfs_d880067__ __obfs_39ea40e164f9__ 
__obfs_781397bc0630__ __obfs_8abfe8__ __obfs_882735cbdfd9f81__ __obfs_f23d125da1e29__ __obfs_4b26dc4663c__ 
__obfs_af1b57__ __obfs_95c9d994f8d75d__ __obfs_0b105cf1504c4e__ __obfs_943aa0fcda4ee2__ __obfs_a18630a__ 
__obfs_f92586a25__ __obfs_b181eaa__ __obfs_a928731e103dfc6__ __obfs_7d2__ __obfs_9308b0d6e58__ 
__obfs_2cfa3753d6a__ __obfs_4764f37856fc727f__ __obfs_2ad__ __obfs_34ffeb359a192eb8__ __obfs_56db57b4db__ 
__obfs_55057122__ __obfs_aba__ __obfs_87ae6f__ __obfs_7553e94d39fd46__ __obfs_e36286b9__ 
__obfs_d2d2c6e2__ __obfs_1b32__ __obfs_240c945b__ __obfs_9d068c869fd3e__ __obfs_9e740__ 
__obfs_532b81fa__ __obfs_9e4__ __obfs_56e6a9__ __obfs_afa299a__ __obfs_4172f3101212a2__ 
__obfs_94ef7214__ __obfs_9fe77ac7__ __obfs_d3802b1d__ __obfs_460b491b9__ __obfs_cb16b8498f7__ 
__obfs_d8c2__ __obfs_7ec3b3c__ __obfs_ee23e7ad9b__ __obfs_64d52e08cc03e60__ __obfs_9d752cb08ef466fc__ 
__obfs_dc0c3__ __obfs_3e195__ __obfs_3db11d259a9db7f__ __obfs_167__ __obfs_208__ 
__obfs_33____ __obfs_63ce12dcf1ede__ __obfs_1f72e258f__ __obfs_09____ __obfs_56517f19__ 
__obfs_6d3a2d2__ __obfs_e8542a04d734d__ __obfs_d884__ __obfs_aaac__ __obfs_f9beb1e__ 
__obfs_685__ __obfs_21ce68__ __obfs_48d__ __obfs_258e1304762902__ __obfs_2e3d2c4f3__ 
__obfs_cd3bbc2d7ca1__ __obfs_91f9fec9__ __obfs_b4affa4f6b27df04__ __obfs_3df0__ __obfs_cbf__ 
__obfs_27e8e17134dd__ __obfs_092cb13c22d5__ __obfs_9332c513ef44b__ __obfs_7ba6d33c__ __obfs_641d77dd5271f__ 
__obfs_211a7a84d3d5c__ __obfs_79cae1be0__ __obfs_d74cb35__ __obfs_28d437661d__ __obfs_4625d8e31dad7d1c__ 
__obfs_7f6___ __obfs_20___ __obfs_83ddfb__ __obfs_5c15__ __obfs_73f104c9fba50050__ 
__obfs_f2_____ __obfs_2119b8d43e__ __obfs_ad___ __obfs_cab070d53__ __obfs_8ce87b__ 
__obfs_3569df15__ __obfs_9fc664__ __obfs_f87e955fd6b89f89__ __obfs_1aa___ __obfs_e16e74a6356__ 
__obfs_44f__ __obfs_3430__ __obfs_f31752__ __obfs_deb74a85a4a6__ __obfs_335d__ 
__obfs_e73fecc08__ __obfs_690bb3__ __obfs_4ecb679f__ __obfs_c157297d1a1ff04__ __obfs_916d3891a243c__ 
__obfs_42547f5a4__ __obfs_41c542dfe6e4f__ __obfs_360__ __obfs_c82836ed448c41__ __obfs_58___ 
__obfs_63c6598__ __obfs_9532__ __obfs_d3614f__ __obfs_e97__ __obfs_37968ad196a5085__ 
__obfs_98cac9d33aad44__ __obfs_5e7__ __obfs_43a115cbd6f4788__ __obfs_cd8d5260c813__ __obfs_38ef4b66__ 
__obfs_02ae6a786b__ __obfs_8068fee5f49946__ __obfs_40db__ __obfs_0a49e3c3a03ebd__ __obfs_c563c2c394023a07__ 
__obfs_143758ee65__ __obfs_c911241__ __obfs_fa6c94460e9__ __obfs_b994697479c5716__ __obfs_eb18482__ 
__obfs_91e5__ __obfs_c04c1__ __obfs_0e57098d03__ __obfs_bca3__ __obfs_67974233917ce__ 
__obfs_c2___ __obfs_a29__ __obfs_b5b8c48482__ __obfs_46d__ __obfs_b7d0858d41a6c__ 
__obfs_fcd__ __obfs_cac8e1__ __obfs_ea9268cb__ __obfs_65b1e92c585__ __obfs_243be2818a23c9__ 
__obfs_1c66f4627f1b9679__ __obfs_6e2eec9__ __obfs_a6ade5aa93__ __obfs_f26df67__ __obfs_9b2f00f37307f2c2__ 
__obfs_dfa037a53e1__ __obfs_7da18d0326a9f__ __obfs_7fa215c9__ __obfs_9eac1__ __obfs_494__ 
__obfs_c6d6445d97e__ __obfs_6236c__ __obfs_a30__ __obfs_42c8938e4cf__ __obfs_4f5a97__ 
__obfs_f550e0ba9e1c4e8b__ __obfs_dc0__ __obfs_582967e09__ __obfs_b9f35816__ __obfs_31__ 
__obfs_d58f855f__ __obfs_4c2e5eaae91__ __obfs_f269__ __obfs_50dd7100__ __obfs_7171e95__ 
__obfs_5a5eab21ca2a__ __obfs_a61__ __obfs_533fa79__ __obfs_c4d2ce3f3ebb5__ __obfs_4f8bc5ac1dc2b4__ 
__obfs_866d90e0921__ __obfs_a9df2255ad642b__ __obfs_8e5__ __obfs_70____ __obfs_2c62__ 
__obfs_c25__ __obfs_551cb238f48950__ __obfs_d35b05a832e2bb9__ __obfs_db346ccb62d4__ __obfs_2ed80f6311c182__ 
__obfs_ccc81a9__ __obfs_834a3bd235bc__ __obfs_8d___ __obfs_9854d7afce41__ __obfs_cc58f7abf0b0c__ 
__obfs_0dd1bc__ __obfs_a1c5aff9__ __obfs_df42e224__ __obfs_51f3eb940fd7__ __obfs_8dcf2420e__ 
__obfs_31___ __obfs_5db60c9820991__ __obfs_9649dec__ __obfs_972__ __obfs_8609__ 
__obfs_cbfe568136__ __obfs_c2c__ __obfs_fb0650__ __obfs_e8d66338fab3727__ __obfs_5c8e07__ 
__obfs_ee188463935a061d__ __obfs_4175f2ebb2__ __obfs_b957__ __obfs_37db6b__ __obfs_fd___ 
__obfs_4837ba5cd49__ __obfs_4fc__ __obfs_1517c8664be__ __obfs_9d949c3d__ __obfs_c09f9caf5e08836d__ 
__obfs_63154d5661f__ __obfs_e593__ __obfs_3341f6f048384e__ __obfs_576d02622__ __obfs_4175a4b46a4__ 
__obfs_1be883eec3231f__ __obfs_1bf50__ __obfs_27b587bbe83ae__ __obfs_b085c4fa543a__ __obfs_b85d65c39e12__ 
__obfs_39__ __obfs_49cbb759277__ __obfs_4d9__ __obfs_859b00aec8885efc__ __obfs_5fc7c9bd1__ 
__obfs_d6525aa8__ __obfs_9b8f0779badba__ __obfs_d90e5b__ __obfs_97f081d3b1__ __obfs_943b5fd1ef60d3a4__ 
__obfs_1340ccf24722f__ __obfs_4fc28b7093b135c__ __obfs_d2__ __obfs_1597d21403__ __obfs_79f69230354b7120__ 
__obfs_679d8bbd776e__ __obfs_acff1af62d0f91f4__ __obfs_c56a022b1525052__ __obfs_298__ __obfs_f8f122d50eba11c3__ 
__obfs_13e36f06c66134ad__ __obfs_70fc5f04320__ __obfs_39486845643__ __obfs_74c__ __obfs_e5afb0f2dbc6d__ 
__obfs_3f___ __obfs_29e1c59be16__ __obfs_ec36e2ba64f__ __obfs_da21ba__ __obfs_f9fe8__ 
__obfs_c3810d4a951__ __obfs_71a__ __obfs_da4f21__ __obfs_6df182582740607__ __obfs_2e5c2cb8d13e8fba__ 
__obfs_bb702465f3c314__ __obfs_7f278ad602__ __obfs_af8d__ __obfs_b928fec5932bf2f__ __obfs_6e2d5d50a943a0e__ 
__obfs_3f900db260__ __obfs_0f3c5d0c3666eec8__ __obfs_86c51678350f656d__ __obfs_bf5cd8__ __obfs_806d92641__ 
__obfs_ac52c6__ __obfs_24e01830d21__ __obfs_6f611188ad4__ __obfs_f51238__ __obfs_dd5__ 
__obfs_db9ad56__ __obfs_43d762__ __obfs_b607ba5__ __obfs_0cbed40__ __obfs_f81dee__ 
__obfs_11bc__ __obfs_cba0a4ee__ __obfs_f2e84d__ __obfs_67800448__ __obfs_9a32ff36c6__ 
__obfs_4f5a9bf135f28535__ __obfs_2ba3c4b9390__ __obfs_7d571e5__ __obfs_a8badd37c221a3__ __obfs_a58616464d142__ 
__obfs_9425b__ __obfs_1bda4__ __obfs_a0443c8c8c33__ __obfs_5e4450dc93010__ __obfs_7059__ 
__obfs_0c2f66f437__ __obfs_540393ae7f8b7a7__ __obfs_4f9c76cf97f8__ __obfs_bbbe7ef28a001__ __obfs_6516c__ 
__obfs_7612936dcc8528__ __obfs_dfbd282c18300fa0__ __obfs_0de5__ __obfs_c12d1f7cc7c4b41__ __obfs_adf8d7f8c53c868__ 
__obfs_d464b5ac9__ __obfs_43e04__ __obfs_abec16f483a__ __obfs_743__ __obfs_9cf742e94f29f45__ 
__obfs_1bd69c7__ __obfs_ffc58105bf6__ __obfs_254ed__ __obfs_3ce83f544dbe6__ __obfs_f8eb27__ 
__obfs_f23b3df__ __obfs_671__ __obfs_ab8__ __obfs_21b5680d__ __obfs_cb5f984421c__ 
__obfs_6693a7a__ __obfs_b14680de__ __obfs_bd3ef5__ __obfs_fbfe5ba2__ __obfs_1cdf14d1e369__ 
__obfs_587524833eaf9__ __obfs_f0___ __obfs_621c090c3a61c__ __obfs_45_____ __obfs_7fc6__ 
__obfs_1192265fb3__ __obfs_aec851__ __obfs_d5ff13537__ __obfs_4e477793df9__ __obfs_31____ 
__obfs_16__ __obfs_c952ce__ __obfs_ac4e7a4f341e7__ __obfs_a09e75c5c86__ __obfs_015e31933__ 
__obfs_084a8a9a__ __obfs_3be0__ __obfs_3cc578f087e__ __obfs_c0c78__ __obfs_7f5fc754c7af0a__ 
__obfs_4f81b1d964419__ __obfs_5b5e__ __obfs_d360a50__ __obfs_56577889__ __obfs_1cd73be1e256a7__ 
__obfs_ca4b3353__ __obfs_da0b566359c__ __obfs_d3f5d4de09ea1946__ __obfs_8fb134f258b1f786__ __obfs_df5354693__ 
__obfs_ee0e95249268b8__ __obfs_354ac345fd__ __obfs_e366d105cfd__ __obfs_5901fe__ __obfs_89a4779d3836__ 
__obfs_38____ __obfs_3e33b9__ __obfs_90____ __obfs_9565f1cd832__ __obfs_5487e79fa__ 
__obfs_8d6a06b2f1208b__ __obfs_9529fbba677__ __obfs_4b04b__ __obfs_8133415ea__ __obfs_75806e8__ 
__obfs_ab2481__ __obfs_f3a3a63__ __obfs_a76d__ __obfs_7d97667a3e056__ __obfs_8430b32b5ba__ 
__obfs_5463b514e21fbd3f__ __obfs_a19883f__ __obfs_e95__ __obfs_23755432da68528__ __obfs_fb4c4__ 
__obfs_d01eeca8b24321c__ __obfs_fa8db__ __obfs_2766__ __obfs_350a3797c__ __obfs_0f9cafd01__ 
__obfs_e3b2125__ __obfs_a3147b8__ __obfs_ec0f40c389a__ __obfs_ad6847__ __obfs_9c9f1366edbae758__ 
__obfs_3b9be7e15b46c4__ __obfs_486c825__ __obfs_02bf8621__ __obfs_e1b90__ __obfs_7ac71__ 
__obfs_fc7615__ __obfs_46123e470d__ __obfs_d2a2c1da__ __obfs_73c140__ __obfs_be93cca18__ 
__obfs_ae___ __obfs_06f2e099b4f871__ __obfs_77340c2e0__ __obfs_101951fe7e__ __obfs_64c5__ 
__obfs_3983e1512aa__ __obfs_f7___ __obfs_da0b1b5bec71__ __obfs_eca89c0554c__ __obfs_68897__ 
__obfs_a3ec6dd8d53871__ __obfs_6abcc8f24321d1eb__ __obfs_9ca8c9b0996bbf05__ __obfs_5e0__ __obfs_e910__ 
__obfs_771__ __obfs_4ca9764c98c__ __obfs_22___ __obfs_b2b7c__ __obfs_6f67057__ 
__obfs_c42f891__ __obfs_64f07f01__ __obfs_fdeea652a89ec3e__ __obfs_4ee78d4122ef8503__ __obfs_ab24cd2b811ee48__ 
__obfs_a5ff5d4b__ __obfs_1e8ca836c962__ __obfs_c1aeb6__ __obfs_de3c1a733c9__ __obfs_1b69ebedb5227000__ 
__obfs_b986700c6__ __obfs_c79ec57a8e72a__ __obfs_6098ed616e71__ __obfs_92f__ __obfs_7dc3338d4__ 
__obfs_5bf__ __obfs_84f7__ __obfs_ca8__ __obfs_770c0e7e2a__ __obfs_7a6a61__ 
__obfs_c929f2210__ __obfs_0314c9b108b8c39__ __obfs_a4d__ __obfs_b2__ __obfs_a6a__ 
__obfs_46fc943ecd5644__ __obfs_93d__ __obfs_6734fa703f6__ __obfs_88479e328a8633f__ __obfs_440924__ 
__obfs_4f05d4821fe9967__ __obfs_5eb13cb69b6e20d__ __obfs_0777acff7c9ab3__ __obfs_6195f47dcff__ __obfs_60__ 
__obfs_a655fb__ __obfs_10___ __obfs_d71__ __obfs_810dfbbebb173020__ __obfs_2d19__ 
__obfs_8b5c844__ __obfs_9f60ab2b5__ __obfs_26ff6f4ca__ __obfs_37588c65__ __obfs_bd22__ 
__obfs_18a9042b3fc__ __obfs_bba6bca05fecde04__ __obfs_b837305e43f7__ __obfs_3e3aa687__ __obfs_ecf5631507a__ 
__obfs_f816dc__ __obfs_174f8__ __obfs_56__ __obfs_60495b__ __obfs_861578d797aeb__ 
__obfs_a7f0d2b95c601__ __obfs_65ae450c5536__ __obfs_e03845__ __obfs_e46bc064f__ __obfs_21__ 
__obfs_adc8ca__ __obfs_1bd36c9a__ __obfs_8ce__ __obfs_2130__ __obfs_f69__ 
__obfs_97008ea270__ __obfs_16d11e959__ __obfs_13b919438__ __obfs_155841__ __obfs_91f573__ 
__obfs_96b250a90__ __obfs_e254457f7497c00f__ __obfs_13e5ebb0__ __obfs_217f5__ __obfs_de043__ 
__obfs_b207f5c5__ __obfs_0ab922b__ __obfs_22cf8d98dca2__ __obfs_c76db12c8__ __obfs_09e7655fc1dc8f__ 
__obfs_77cd__ __obfs_331cc28f8747a__ __obfs_cd474f6341__ __obfs_3770282ae7c0e576__ __obfs_99296__ 
__obfs_a5e308070bd__ __obfs_0fd4b8a8354a77__ __obfs_2bce32ed409__ __obfs_0b0b0__ __obfs_e0c7ccc4__ 
__obfs_86dba8__ __obfs_0530e__ __obfs_7d265aa7__ __obfs_7e_____ __obfs_3335881e0__ 
__obfs_227__ __obfs_769ac34a401__ __obfs_d7b__ __obfs_4a71e49f6bd__ __obfs_590494d54ebe8e__ 
__obfs_ef35613fc5fa4c4__ __obfs_e3b0ab92511ce__ __obfs_44___ __obfs_872__ __obfs_76c__ 
__obfs_1d54c76__ __obfs_bd85__ __obfs_81__ __obfs_d278df491945319__ __obfs_d4b__ 
__obfs_35d02fef7d__ __obfs_74d90aafda__ __obfs_04115ec378e476c__ __obfs_f42a3__ __obfs_690__ 
__obfs_d0ac1ed0__ __obfs_82____ __obfs_aafd8346a677a__ __obfs_e464f78__ __obfs_5dcd0ddd3d918c70__ 
__obfs_c0e19ce0dbabb__ __obfs_dd1016d__ __obfs_3b24156ad56__ __obfs_47257__ __obfs_fd45ebc1e1d__ 
__obfs_8ccfb114__ __obfs_70d5212dd052b2e__ __obfs_5d151d1059a62__ __obfs_d40e0a2a__ __obfs_887a185b1a40801__ 
__obfs_fd272fe04b__ __obfs_28f72__ __obfs_fe7ecc4de28b2c83__ __obfs_5e__ __obfs_7369f3c86__ 
__obfs_e546594ad40__ __obfs_69295f5f6bd__ __obfs_f40ee694989b__ __obfs_5f24__ __obfs_8c26d2fad09dc__ 
__obfs_fcac695db02687f__ __obfs_608b__ __obfs_7bfa32686__ __obfs_6a18__ __obfs_29c0c0ee22385__ 
__obfs_87d__ __obfs_ec9__ __obfs_c5e1ab9c931df8f__ __obfs_be3ac64e67e84198__ __obfs_094bb65__ 
__obfs_5101a4796c512__ __obfs_13384ffc9d8bdb21__ __obfs_5d0cb12f8c9ad684__ __obfs_33dd6d__ __obfs_dc49__ 
__obfs_53c5b2aff__ __obfs_0e139b17__ __obfs_fb___ __obfs_f0f6cc51dac__ __obfs_bedc7106ffa9616d__ 
__obfs_39b8f__ __obfs_05128e4__ __obfs_34609bd__ __obfs_b1b0ef5ba6b5__ __obfs_ddf88ea6__ 
__obfs_eaa__ __obfs_9fe4e15b3__ __obfs_18a__ __obfs_97e484__ __obfs_120ca817ebe8caa7__ 
__obfs_55603a5f239e4__ __obfs_a732804c8__ __obfs_f60ce002e5182e7__ __obfs_3e1953b5725__ __obfs_41b0db49f__ 
__obfs_63cb524a9__ __obfs_fa612be4940bae1__ __obfs_ccb421d5f36c5a__ __obfs_7ec12a__ __obfs_2b8f621e9244cea__ 
__obfs_27584e8__ __obfs_148d__ __obfs_8d8f733a7c2a2e__ __obfs_7d___ __obfs_11d__ 
__obfs_a57d48399922b034__ __obfs_beda24c1e1b__ __obfs_30cde89544__ __obfs_5dd3e474__ __obfs_cabad3b9bc0af__ 
__obfs_ac___ __obfs_147540e129e096f__ __obfs_b90ba8__ __obfs_b052e2e0c0a__ __obfs_7e889fb76e0e07c1__ 
__obfs_d6cf4da5ce__ __obfs_b0__ __obfs_38087__ __obfs_8cb94e7a9661ea20__ __obfs_f2b5e92f6__ 
__obfs_c96c08f8b__ __obfs_a7__ __obfs_27d8__ __obfs_7716d0fc316__ __obfs_2bf7e9e8f3f3bc__ 
__obfs_8526e0962a844e4a__ __obfs_9a86d53__ __obfs_d290__ __obfs_3e6ad89fe36__ __obfs_8e1ad7941398486__ 
__obfs_e0640c__ __obfs_d935__ __obfs_31_____ __obfs_b5b1d__ __obfs_f569__ 
__obfs_d3e8fc83b3__ __obfs_9033__ __obfs_ce0__ __obfs_1343777b8ead__ __obfs_2c7f9ccb__ 
__obfs_0d5bd023a3ee1__ __obfs_c6447300d99fdbf4__ __obfs_f2c3b258__ __obfs_40ccca__ __obfs_da___ 
__obfs_f1676935f9304__ __obfs_672d30ab508__ __obfs_583cf6a454__ __obfs_a546203__ __obfs_fead__ 
__obfs_61f3a6dbc9120ea__ __obfs_f291e10e__ __obfs_1f5e7f2748adabf__ __obfs_2000f63__ __obfs_3c741__ 
__obfs_e8aac012__ __obfs_e02a35__ __obfs_64b3ec1fdfacead__ __obfs_475d66__ __obfs_a6d5ab67798__ 
__obfs_244edd7e85dc__ __obfs_d8a4e572d866aa__ __obfs_b85__ __obfs_48a79bcf60__ __obfs_46d___ 
__obfs_8710ef761b__ __obfs_a8ef__ __obfs_167434f__ __obfs_e8432fb72c61c906__ __obfs_961b2__ 
__obfs_b74084f__ __obfs_9c__ __obfs_52c670__ __obfs_c0a62e__ __obfs_977b33ace8251dd__ 
__obfs_d3e0f__ __obfs_db209d71df5__ __obfs_1138d90ef0a__ __obfs_ae0909a324f__ __obfs_665d5cbb82b5__ 
__obfs_9ee70b798__ __obfs_1377e22fd810__ __obfs_1e51e0__ __obfs_a118806694c9d__ __obfs_526c321538d951f__ 
__obfs_f06ae085__ __obfs_789a283923__ __obfs_8f04ac8eadb8__ __obfs_50a074e6a__ __obfs_1f187c8bc462__ 
__obfs_2b1905b5d4641__ __obfs_d2e__ __obfs_9bab734__ __obfs_6de4bfe9504589a__ __obfs_12e59a33d__ 
__obfs_65f148__ __obfs_4bb94__ __obfs_6b4e2b9376139__ __obfs_4738__ __obfs_0d27688c6__ 
__obfs_8fc983__ __obfs_41bcfd9ab65__ __obfs_086af__ __obfs_03593ce517fe__ __obfs_096__ 
__obfs_f016f25df05b5b1b__ __obfs_b4aa00bc1c59b__ __obfs_402b0__ __obfs_9dee60d3205c__ __obfs_bdb__ 
__obfs_3ce3bd7d63a2c9c8__ __obfs_2120606d6a__ __obfs_19485224d__ __obfs_702cafa3bb4c9__ __obfs_3d8e03e8b133b16f__ 
__obfs_bd470ca955d94__ __obfs_ae8__ __obfs_0307fec2cef6aec3__ __obfs_c793b3be8f1__ __obfs_d1f44e2f0__ 
__obfs_ea96efc__ __obfs_e243a__ __obfs_6cf821bc9__ __obfs_aa___ __obfs_9d740bd0f36aaa__ 
__obfs_2bf5e202fc973a02__ __obfs_1da54__ __obfs_dc2208f9bbd1148__ __obfs_3bcf__ __obfs_65a99bb7a3115__ 
__obfs_fc8fdb29501a__ __obfs_12ced__ __obfs_d71f51424__ __obfs_b4d__ __obfs_83451e7ef8755c2a__ 
__obfs_a4d4__ __obfs_125c0e943c7__ __obfs_1d8d70dddf14__ __obfs_1f9b616__ __obfs_0bd65__ 
__obfs_ce___ __obfs_1713a__ __obfs_da9__ __obfs_60___ __obfs_3c8__ 
__obfs_3bc3e78c17d35__ __obfs_a1f0cf94512f__ __obfs_4bbbe6cb59__ __obfs_b0___ __obfs_7c5845__ 
__obfs_7f2be1b45d278__ __obfs_51a472c08__ __obfs_77305c2__ __obfs_3c3c139b__ __obfs_db____ 
__obfs_58079__ __obfs_0887__ __obfs_6fd6b030c6afec__ __obfs_53e19f3dbb211f__ __obfs_5ada__ 
__obfs_7230b2b03__ __obfs_6d4f95bf53bb__ __obfs_1f88c7c5d7__ __obfs_fd95e__ __obfs_80c94c09__ 
__obfs_d2b15c75c0c389b__ __obfs_8ab8d__ __obfs_70afbf2259__ __obfs_4e2ecebbfafe27a7__ __obfs_e9ed9cad56c9__ 
__obfs_61b__ __obfs_e0eacd9839716343__ __obfs_0b5e29a__ __obfs_043ab__ __obfs_f937c8fddbe66a__ 
__obfs_30da227c6b5__ __obfs_4e46e9__ __obfs_995__ __obfs_88c040adb393__ __obfs_e0f12__ 
__obfs_a3ab4ff8fa4deed2__ __obfs_0fd__ __obfs_103__ __obfs_f8151fd__ __obfs_0e1feae55e36__ 
__obfs_60dcc0d0012f30__ __obfs_ab6439__ __obfs_d03a857a23__ __obfs_2d3b02917ea2900__ __obfs_c89ca3__ 
__obfs_34f9a343f945196__ __obfs_6c530aae__ __obfs_cc8__ __obfs_4607f7ff__ __obfs_803ef56843__ 
__obfs_bf499a12e998__ __obfs_a4d3a__ __obfs_14da92f2bdae__ __obfs_c4819d06b__ __obfs_ef0eff608__ 
__obfs_46489c17893dfdcf__ __obfs_a75a52f__ __obfs_88____ __obfs_438124b4c__ __obfs_173__ 
__obfs_d84210a75448__ __obfs_bdf3fd65c814__ __obfs_00b7__ __obfs_6f3a770e__ __obfs_5e51__ 
__obfs_7d6548bd__ __obfs_1a15d41__ __obfs_76__ __obfs_09a__ __obfs_124461dcd357__ 
__obfs_14____ __obfs_075b24__ __obfs_7d411dca734832__ __obfs_2ff385c6e__ __obfs_f8ea2e__ 
__obfs_989652eef28bc49__ __obfs_475fbefa9ebfb__ __obfs_63c4b1baf3b4460__ __obfs_21___ __obfs_e2f374c3418__ 
__obfs_bf56a1b37b94243__ __obfs_573f7f25b7__ __obfs_710__ __obfs_597__ __obfs_bbc92a__ 
__obfs_45e81409831b77__ __obfs_752d2c9ecfe__ __obfs_f110a326be69__ __obfs_8620005ac78d8257__ __obfs_37b__ 
__obfs_9f1f64__ __obfs_1dfcb0__ __obfs_012__ __obfs_591126__ __obfs_9713faa264__ 
__obfs_983a33__ __obfs_543857f4a06c8__ __obfs_1d38dd921e__ __obfs_56a8da1d3bcb2__ __obfs_72__ 
__obfs_aee1bc7fa__ __obfs_cfb__ __obfs_26310c700ffd1b5__ __obfs_79fde5402cb__ __obfs_edb684859b848362__ 
__obfs_0f65caf0a7d00afd__ __obfs_2f3c6__ __obfs_7c33e57e3dbd__ __obfs_da974f5eba194__ __obfs_78f18936__ 
__obfs_1f6419b1cb__ __obfs_09de__ __obfs_3910d__ __obfs_7a__ __obfs_3eb2f1a06667b__ 
__obfs_62021a1833__ __obfs_19eca5979ccb__ __obfs_f8905bd3df64ace__ __obfs_ccb1d57d7fa17c6__ __obfs_e7023__ 
__obfs_90306a__ __obfs_6f518c31f6__ __obfs_359___ __obfs_952575__ __obfs_a5b93aaec935a__ 
__obfs_6b0503__ __obfs_cb3ce9b__ __obfs_4454c95ca2__ __obfs_d74a21__ __obfs_75___ 
__obfs_d143__ __obfs_861637a425ef06e6__ __obfs_6562c5c1f33d__ __obfs_bcfa8a78__ __obfs_f1920129f9c75b3d__ 
__obfs_e9dae4__ __obfs_bfd2308e9e__ __obfs_df__ __obfs_0b24d8469d6c__ __obfs_ddac1f6f13bb37__ 
__obfs_31784d9fc1fa0__ __obfs_f89394c979b34__ __obfs_70b8fe090143d__ __obfs_c2890d4__ __obfs_2f39__ 
__obfs_3ac48664b7886c__ __obfs_c78c347465f477__ __obfs_f1298750ed096187__ __obfs_33805671920f0__ __obfs_6ba108__ 
__obfs_43cf3ae60__ __obfs_e2c4__ __obfs_41c__ __obfs_fa1317__ __obfs_4ef1477dc9__ 
__obfs_cfe912f5cb3aa57__ __obfs_f58__ __obfs_501627aa14__ __obfs_a613863f6a3__ __obfs_28659414dab9ec__ 
__obfs_2f364281f619584__ __obfs_ed46558a56a4a2__ __obfs_aaebdb__ __obfs_85e5526a360b0__ __obfs_f0f800c92d1__ 
__obfs_5c3b99e8f9__ __obfs_6d0c932802f69__ __obfs_fd00d__ __obfs_be7485be5b6eb36__ __obfs_d630553e__ 
__obfs_971eb27c63__ __obfs_c850c5__ __obfs_f2708856060b3b50__ __obfs_3cfacd__ __obfs_e661551c8e__ 
__obfs_70_____ __obfs_14f2ebeab937ca12__ __obfs_000871c1fc726f0b__ __obfs_eeaebbffb5d2__ __obfs_0ac0891__ 
__obfs_8011ecba397__ __obfs_761e6675f9e546__ __obfs_0397__ __obfs_b9a8f4af__ __obfs_1bf2e__ 
__obfs_54843973f9b__ __obfs_5739fb4e82ed5366__ __obfs_e93__ __obfs_83__ __obfs_9d8__ 
__obfs_1e5186bca8f75f__ __obfs_d3f93e7__ __obfs_0d1a9651__ __obfs_73634c1dcbe__ __obfs_bd5c5e1__ 
__obfs_06_____ __obfs_3b3fff646346__ __obfs_15____ __obfs_96__ __obfs_18fc72d8b8ab__ 
__obfs_1013c8b99e6__ __obfs_50adec__ __obfs_fcfe9c770e__ __obfs_f08__ __obfs_33b879e7ab79f56a__ 
__obfs_080c993fb3b5__ __obfs_5ffaa9f5182c2a__ __obfs_63c17d596f__ __obfs_77c6713209__ __obfs_30d411fdc0e6d__ 
__obfs_a4814fbe4abda__ __obfs_50f3f8c42__ __obfs_250dd5681__ __obfs_8f4__ __obfs_205c__ 
__obfs_d19544__ __obfs_a8f12d9486cbcc__ __obfs_d8074a35855a__ __obfs_b15__ __obfs_6ab__ 
__obfs_ab3f9cab2__ __obfs_555638__ __obfs_ec1c5914104__ __obfs_cd61a580392a__ __obfs_8685549650016d__ 
__obfs_ee0b86d2__ __obfs_f621585d__ __obfs_f64b2463cf1__ __obfs_c82a7178ece0__ __obfs_fc452__ 
__obfs_7c0f63c15__ __obfs_9f9e8c__ __obfs_fbad540b2__ __obfs_6b9bb055__ __obfs_ccc36675__ 
__obfs_d6____ __obfs_722c__ __obfs_85203ae8__ __obfs_cfd__ __obfs_1f5__ 
__obfs_6c2e49911b68d__ __obfs_ea6979872125d__ __obfs_82_____ __obfs_ac4d17__ __obfs_97788__ 
__obfs_4f5c4__ __obfs_d26beb4__ __obfs_75____ __obfs_d1e96978c6935ec0__ __obfs_4aaa76178f856__ 
__obfs_5265d33c184a__ __obfs_3b9d6e5e7__ __obfs_fc152e73692bc3c9__ __obfs_e4a__ __obfs_0e__ 
__obfs_5c645c__ __obfs_ba9fab001f__ __obfs_dba1cdfcf635938__ __obfs_1f____ __obfs_c80bcf42c__ 
__obfs_5034a5d__ __obfs_b7d35509ab19__ __obfs_700fdb2b__ __obfs_1068bceb1__ __obfs_4772c1b987f1f6d__ 
__obfs_c4414e538a5475__ __obfs_a9ad5f2808f68ee__ __obfs_84fdbc__ __obfs_ac4395adcb__ __obfs_ec___ 
__obfs_d33174__ __obfs_daad8d509__ __obfs_9fd98f856d3ca208__ __obfs_db182d255__ __obfs_bc9c8c705927__ 
__obfs_a7___ __obfs_b52340b4de4__ __obfs_bd29__ __obfs_007d4__ __obfs_cb59b747__ 
__obfs_5b0fa0e4__ __obfs_bc5fcb0018ce__ __obfs_1a3__ __obfs_bb181e83b9a__ __obfs_da2__ 
__obfs_d71dd235__ __obfs_c47e937423877__ __obfs_f1b035b71ef5f__ __obfs_53420b__ __obfs_dd03d__ 
__obfs_102b905d54a908ae__ __obfs_f9___ __obfs_6fb52e__ __obfs_71f0__ __obfs_a425__ 
__obfs_13d7dc09__ __obfs_096ffc29920__ __obfs_fd1d83de25__ __obfs_901797aebf0b23ec__ __obfs_37__ 
__obfs_a512294422de868__ __obfs_8df6a65__ __obfs_b22ed7eaf__ __obfs_c2e0__ __obfs_f3507289cfdc8c9a__ 
__obfs_0f3__ __obfs_a55__ __obfs_a0205__ __obfs_db9e6eef2eb__ __obfs_42778ef0b5805__ 
__obfs_01b6__ __obfs_de9051__ __obfs_b645e524a1512ce__ __obfs_b65f2__ __obfs_91665__ 
__obfs_39dd987a9d2__ __obfs_ebad33b3__ __obfs_91299__ __obfs_dfc6__ __obfs_84899ae725ba49__ 
__obfs_a7____ __obfs_c678aec6e8__ __obfs_d80__ __obfs_0b__ __obfs_d914a6c6d9__ 
__obfs_e7d1__ __obfs_0d2b2__ __obfs_ea81a__ __obfs_191c__ __obfs_f60f6b0d1__ 
__obfs_cfe795a0a3__ __obfs_9abe36658bff81__ __obfs_a3f61f3a8034cbfb__ __obfs_1a77befc3b6__ __obfs_dab10c50dc__ 
__obfs_dcf908__ __obfs_6a57__ __obfs_c5d___ __obfs_3eae62bba9ddf6__ __obfs_8c5ebe8__ 
__obfs_538a50f__ __obfs_04c690__ __obfs_c3___ __obfs_085ccaddbd3aa__ __obfs_eafc8fe9c61d67__ 
__obfs_1e__ __obfs_7a50d__ __obfs_a376802c0811f1b9__ __obfs_82______ __obfs_5de__ 
__obfs_1d0787d664c95f__ __obfs_1d3b7f1f8a762__ __obfs_c5c1bda11__ __obfs_48c00ae965e23b2__ __obfs_6adbe8b2__ 
__obfs_9a02387b02ce__ __obfs_b87517__ __obfs_4ff3e350028d0cfc__ __obfs_b28d8e3ccb1f__ __obfs_18a4e13__ 
__obfs_ad____ __obfs_c96ebeee0519963__ __obfs_cede__ __obfs_d6317f80523fdf2__ __obfs_fecc3a370a23d13__ 
__obfs_0c4a4__ __obfs_0c7119e3a6a__ __obfs_137bdd55f159c4f5__ __obfs_2912bbeedc16c__ __obfs_45c68484c6fc509c__ 
__obfs_a821a161aa__ __obfs_1cc8a8ea51cd__ __obfs_f7dafc__ __obfs_22____ __obfs_a5bad363fc4__ 
__obfs_b112ca4__ __obfs_810bf83c7adfd8__ __obfs_7c__ __obfs_187acf7982__ __obfs_084afd913ab1e6ea__ 
__obfs_ed519c02f134f2c__ __obfs_cefb500a__ __obfs_7e6ff020574__ __obfs_e88f243bf__ __obfs_30d4__ 
__obfs_79c__ __obfs_85267d349a__ __obfs_af8d1eb2201864__ __obfs_0f089a__ __obfs_2edfea__ 
__obfs_9238b8c48__ __obfs_a34e1__ __obfs_5857d68cd9280b__ __obfs_de3f712d1a__ __obfs_926ec030f29f83ce__ 
__obfs_7e______ __obfs_f720ec3e5486f__ __obfs_0a934__ __obfs_41____ __obfs_40cb22898__ 
__obfs_2054645718__ __obfs_768e78024__ __obfs_274a10__ __obfs_bdeeecd97__ __obfs_4b0a0290__ 
__obfs_74249__ __obfs_05ee45de8__ __obfs_c4616f5a24a66__ __obfs_022400dff__ __obfs_e6cc4__ 
__obfs_1e8eec__ __obfs_ce6babd06__ __obfs_038__ __obfs_3e9f0fc9b2f8__ __obfs_ec1f764517b__ 
__obfs_549406__ __obfs_5d40954183d62__ __obfs_5cf68969fb67__ __obfs_8122__ __obfs_0c6b6f19684ed9b__ 
__obfs_b8__ __obfs_06f__ __obfs_6245__ __obfs_aea94dc__ __obfs_7aa685b3b1dc1d67__ 
__obfs_f0bf4a2da952__ __obfs_933670f__ __obfs_3713bdd__ __obfs_2cfa8f9e5__ __obfs_a68259__ 
__obfs_d91caca74114d81__ __obfs_d40__ __obfs_9ac5a6d86__ __obfs_f5e647292cc4e__ __obfs_20cf775fa6b5dfe6__ 
__obfs_3c5__ __obfs_a9c397afa__ __obfs_02b5b45ce743b__ __obfs_945__ __obfs_fb09f481d4__ 
__obfs_cf040fc710__ __obfs_77bdfcf__ __obfs_b71155d90aef3b__ __obfs_aa108f56a10e7__ __obfs_606c9__ 
__obfs_2fe5a27c__ __obfs_c6ede20e6f59__ __obfs_c348616cd8a86e__ __obfs_1f2b325dcda__ __obfs_c133fb1bb634a__ 
__obfs_6c35083f35__ __obfs_816__ __obfs_0b081776bae79__ __obfs_0b846__ __obfs_cf63547fadc1aa6__ 
__obfs_060__ __obfs_e9257036daf2__ __obfs_b607a__ __obfs_68d374__ __obfs_723dadb8c69__ 
__obfs_f083__ __obfs_7a9a322cbe0d06__ __obfs_001a__ __obfs_1770ae9__ __obfs_3a4__ 
__obfs_b9__ __obfs_a08e32d2f9a8b__ __obfs_e7a425c6ece20cb__ __obfs_769c3bc__ __obfs_d5036c64412973__ 
__obfs_522e1ea43__ __obfs_54c3d58c5efcf59__ __obfs_0e4ce__ __obfs_1b33__ __obfs_457ded6f20b28fe__ 
__obfs_43975bc2dfc__ __obfs_68abef8ee1ac9__ __obfs_4a45__ __obfs_956685__ __obfs_86a2f353e1e__ 
__obfs_e4a86__ __obfs_f5e62af8__ __obfs_cf8d8__ __obfs_e7e8f8e5982b32__ __obfs_76b7a3a5cf67f3c4__ 
__obfs_d1942a3ab0__ __obfs_b64a7__ __obfs_79e785d63f003__ __obfs_4fb8a7__ __obfs_427e3427c5__ 
__obfs_eaae5e04a259d0__ __obfs_502cbcfede9f1df__ __obfs_50d2d22__ __obfs_6e616e79d491ba4__ __obfs_ee39e503b6bed__ 
__obfs_aba22f748b1a6df__ __obfs_8c53d3__ __obfs_b3746__ __obfs_db8419__ __obfs_4dc3ed__ 
__obfs_991327d63593b0ba__ __obfs_64a7157cf__ __obfs_57cd30d908__ __obfs_ec16c57ed363__ __obfs_9a3f263a5e5f__ 
__obfs_2458ab18be2a__ __obfs_b43a6403__ __obfs_31bd51a7403b__ __obfs_3fc0a5dc1f57__ __obfs_3e441eec3__ 
__obfs_db095bd14b8__ __obfs_280c__ __obfs_429e4a44bec54__ __obfs_5cbb__ __obfs_3418__ 
__obfs_f6a4f71e72dfe0__ __obfs_8cbe9ce__ __obfs_4f____ __obfs_4ae1e2b07ec__ __obfs_87ba276ebbe5__ 
__obfs_60ce367__ __obfs_d8____ __obfs_78e8df__ __obfs_09a8a8976__ __obfs_0e64a__ 
__obfs_1216a1__ __obfs_04992c5115a2c2__ __obfs_66bf858e1194__ __obfs_40170__ __obfs_02052__ 
__obfs_2c6a0bae0f071__ __obfs_30d__ __obfs_77d2afcb31f6__ __obfs_a48251d4c__ __obfs_2f3bbb973063__ 
__obfs_f1e___ __obfs_a600bd172fcabd__ __obfs_e32c51ad3972__ __obfs_33b9c7c18__ __obfs_34adeb__ 
__obfs_0f2818101a7ac4b9__ __obfs_4fe5149039b5276__ __obfs_94bb077f18daa__ __obfs_10ff0b5e85__ __obfs_9f96f36b__ 
__obfs_4ffbd5c8221d7c__ __obfs_8396b14__ __obfs_8e__ __obfs_124c3e4__ __obfs_f1ababf130__ 
__obfs_785ca71d2c85e3__ __obfs_43b9787b8a0cd00a__ __obfs_13bf4a9637__ __obfs_fc146be0b230d7e0__ __obfs_c457d7ae48d08a6b__ 
__obfs_1f8fe28e9283__ __obfs_d4b5b5c16__ __obfs_290ff0feb0__ __obfs_bf40f0ab4e5e6__ __obfs_1fd09c5__ 
__obfs_6dbbe__ __obfs_e586a4f55fb43a54__ __obfs_ccf8111910__ __obfs_2cb__ __obfs_54fe976ba170__ 
__obfs_a3__ __obfs_03b2__ __obfs_415585__ __obfs_240ac9371ec__ __obfs_32___ 
__obfs_1d6408264d31d4__ __obfs_2c27a260f16ad3__ __obfs_351869bde8b9__ __obfs_b3848d61bbbc62__ __obfs_e9470886eca__ 
__obfs_999028872cf__ __obfs_0342c9a7b544__ __obfs_f0873a91b49__ __obfs_e140dbab4__ __obfs_4424d2d__ 
__obfs_747c1bcceb6109a__ __obfs_7e3315fe390974fc__ __obfs_0af78794587__ __obfs_714__ __obfs_53f___ 
__obfs_b28d7c6b6aec0__ __obfs_2f__ __obfs_e36258__ __obfs_b17c0907e67__ __obfs_d62bc__ 
__obfs_b6e584419__ __obfs_f02208a057804e__ __obfs_85___ __obfs_bf8dd8c6__ __obfs_ca17__ 
__obfs_faa___ __obfs_e327b1649__ __obfs_a7971abb4134f__ __obfs_91c77393975889bd__ __obfs_2e2079d633482__ 
__obfs_aac933717a429f__ __obfs_c731__ __obfs_97__ __obfs_335cd1b90b__ __obfs_6651526b6fb8f2__ 
__obfs_79c662560b0a5f1__ __obfs_c7502c55__ __obfs_ba6d843e__ __obfs_b6f8dc086b2d60__ __obfs_99674__ 
__obfs_56bd37d3a2f__ __obfs_8cea559c47__ __obfs_1dba3025b15__ __obfs_c7b4bb942f0b5d__ __obfs_9718db12cae6be__ 
__obfs_8977ecbb8__ __obfs_744878fbdd2687__ __obfs_86b__ __obfs_4aeae1__ __obfs_64ee__ 
__obfs_be__ __obfs_2654__ __obfs_79a3308b13c__ __obfs_7ffb__ __obfs_70117ee3c0__ 
__obfs_8d749ea54f665__ __obfs_f466e84e__ __obfs_05c7ac946880ad__ __obfs_35a0f19__ __obfs_1e747ddbea997a__ 
__obfs_ac____ __obfs_bdb3c278f45e6__ __obfs_080__ __obfs_9f4768b4bd4__ __obfs_739cf54211aa6b7__ 
__obfs_8074856808ebec0c__ __obfs_785736838d7b51f2__ __obfs_a6e8ad49__ __obfs_4ac7__ __obfs_e1cd50f4a__ 
__obfs_23685a24__ __obfs_4a64d9__ __obfs_2e855f9489df__ __obfs_e1054bf2d7__ __obfs_a0___ 
__obfs_d3f06eef2ff__ __obfs_a4bd4d2__ __obfs_fe66__ __obfs_47e338b3c082__ __obfs_a714ec6796f__ 
__obfs_9ce__ __obfs_71e63ef5__ __obfs_043c2ec6c6390d__ __obfs_04fcc65450efc__ __obfs_12b6__ 
__obfs_98c56bce7__ __obfs_237__ __obfs_73d915c91b99__ __obfs_197838c__ __obfs_358f9e7be09177c1__ 
__obfs_45be58__ __obfs_90fd4__ __obfs_5a9__ __obfs_f5ac21cd0ef1b8__ __obfs_6e66329891c__ 
__obfs_91bc33__ __obfs_48f7d3043bc03e6c__ __obfs_2c___ __obfs_03a3655fff3__ __obfs_6a6610feab86a__ 
__obfs_91a4d__ __obfs_173f0f__ __obfs_9f93557d309f65__ __obfs_4eff0720836a198__ __obfs_7a0c1035bc__ 
__obfs_3f1656d96__ __obfs_250b164d84ea39a__ __obfs_9a0ee0a9__ __obfs_2406a0a94c80__ __obfs_9e95248d9b714a9__ 
__obfs_d32__ __obfs_878a0658e652__ __obfs_ae0e__ __obfs_4ffb0__ __obfs_a5fdfa672284da6__ 
__obfs_fa246d0262c__ 