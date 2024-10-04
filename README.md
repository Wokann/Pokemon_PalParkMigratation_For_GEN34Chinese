# Pokemon_PalParkMigratation_For_GEN34Chinese
This project is for chinese fan translation gen3 and gen4 which can let chinese char be transfer through pal park.

Charmap for gen3 chinese translation is based on GB2312 two byte for one char and custom mapped. <br>
The high byte range from 0x01-0x1E and not include 0x06('É') or 0x1B('é') <br>
The low byte range from 0x00-0xF6 which not include DYNAMIC byte and EOS byte.

Charmap for gen4 chinese translation which made by yyjoy (DP) is based on GB2312 and custom mapped.<br>
Charmap for gen4 chinese translation which made by acg (Pt\HGSS) is not based on any existing text encoding.<br>
Charmap for gen4 chinese translation which fixed by xzonn based on previous version has a changing text encoding.<br>
-DP: <= 0.9.0b based on GB2312; >= 2.0.0 based on acg(Pt) extended charmap.<br>
-Pt: based on acg(Pt) extended charmap.<br>
-HGSS: based on acg(Pt) extended charmap.

PalParkMigratation code v1.0 <br>
It is used for yyjoy (DP) and xzonn&yyjoy (DP) <= 0.9.0b. <br>
cause at that time xzonn&acg (Pt\HGSS) didn't extend as much char for GB2312.

PalParkMigratation code v2.0 <br>
It is used for xzonn&yyjoy (DP) >= 2.0.0 and xzonn&acg (Pt\HGSS) >= 2.0.0. <br>
At that time, all version has the same charmap, and extended enough for GB2312.

This project can also be used for other language fan translation project to trans custom char from gen3 to gen4. <br>
such as gen3 Korea translation to gen4 offical Korea version. just change core codes and conversion table for your charmap
