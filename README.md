# Komplex számologép
BME Mérnökiformatikus alapszak 2021/2022 Programozás alapjai nagy házi, komlex számológép.

## Specifikáció
/* komplex számológép, svg file-ba írja a számsíkon ábrázoltakat. Beolvas és 
tárol komplex számokat, átalakít az alakjai között. Tudnia kell összeadni, 
szorozni, osztani, egész hatványozni, és valamint svg file-ban a számokat 
ábrázolni a komplex számsíkon. */ 
### A program célja 
Egy komplex számológép, komplex számokat tárol, fogad, összead, kivon, összeszoroz, eloszt, és 
egész kitevőjű hatványra emel. Menüvezérelt program, ki lehet lépni a programból, számot 
beolvasni, valamint műveletet végezni a menüből, illetve az eltárolt számokat egy svg file-ba 
kimenteni, ezzel ábrázolva őket a komplex számsíkon. A program menüparancsra tudja elmenteni 
az aktuálisan tárolt komplex számokat egy txt file-ba.

### A program használata 
A program futtatás után kiírja a főmenüt és opcióit (fent: beolvas, művelet, ábrázolás, számok 
mentése, kilépés). 
A beolvasás opciót választva kell kiválasztani, hogy algebrai vagy trigonometrikus alakban 
kívánja a felhasználó megadni a számot vagy txt-ből olvassa be (később). Ez után kell a számokat 
megadni szóközzel elválasztva, algebrai alak esetén valós rész, képzetes rész sorrendben (Re Im), 
trigonometrikus alak esetén hossz majd argumentum, azaz szög (fokban) sorrendben (r Φ), ez 
követően mindkettőt enter lenyomásával átadni a programnak. Ez után a program kiírja, hogy 
milyen néven (azonosító 16 számrendszerű számmal) mentette el a számot, így lehet később erre 
a számra hivatkozni. A menü újra megjelenik.

A műveletek: A műveletek menüpont kiválasztása 
után jelenik meg a műveletek almenü. Ezt az almenü 
is részletezi majd. A táblázat mutatja a műveletek 
adatait, szóközzel elválasztva várja a program (a 
nagybetű kisbetű mindegy). Az „1A2” és „1A3” a 
már memóriában eltárolt számokhoz rendelt 
azonosítók. A sorrend a kivonásnál és az osztásnál 
értelemszerűen először a kisebbítendő vagy osztandó majd a kivonandó vagy osztó. A kívánt alak 
pedig egy „T” (trigonometriai) vagy egy „A” (algebrai). A program ismer egy „ANS” operandust, 
amely mindig az utolsó kiszámolt értére mutat. A választást enterrel kell véglegesíteni. 

Ez után a program kiírja az így kapott számot, és annak a betűazonosítóját, amelyet a program 
maga választ, ennek változtatására nincs lehetőség. 
Ábrázolás opció: a program az összes memóriában tárolt számot kiírja egy svg file-ba, ez a file-ba 
írás egyirányú, innen a program nem tud visszaolvasni. A program készít egy `szamsik.svg` 
file-t, és azt megnyitva tekinthető meg az ábrázolás. 
Számok mentése: A beolvasás elérhető a beolvasás menü alatt, ilyenkor megnyitja a 
`szamok.txt` nevű file-t és beolvassa a benne tárolt számokat. Majd eltárolja azokat. 
A számokat a főmenüben a mentés opcióval lehet menteni, ilyenkor az esetleg létező file-t felülírja. 
A számtárolás módja: alak (T/A), szóköz, betű azonosító, szóköz Re/r szóköz Im/Φ (szög fokban) 
új sor. 
Példa:

```
T 1A2 4 60 
A 1A3 3 5 
```

Ez például két számot tárol, az elsőt „1A2” azonosítóval, trigonometrikus alakban, melynek valós 
része 3 képzetes része pedig 5, majd egyet „1A3” azonosítóval algebrai alakban melynek hossza 
4 és argumentumszöge 60°.

## Dokumentáció
### Általános (felhasználói) dokumentáció 
Ez egy komplex számológép, komplex számokat lehet tárolni, és azokkal számolni, a be és 
kimeneten mindkét alakban akár. 
A főmenüben jelenleg 4 opció létezik, beolvasás, műveletvégzés, a számok elmentése, valamint 
a kilépés. A menüket a felsorolt betűkkel lehet elérni (a nagy és a kisbetű mindegy) majd enter. 
Minden a programnak beadni kívánt adatot enterrel kell véglegesíteni, kivéve a műveleteknél. Az 
beolvasás menü az I alatt van, itt egy újabb menü fogad, ahol ki lehet választani, hogy egy létező 
file-ból (szamok.txt) vagy az ablakba szeretnénk beírni, ha az ablakba akkor milyen alakban. A 
file-ból a beolvasás parancsra automatikusan működik, az alak kiválasztása után pedig meg kell 
adni valós részt és képzetes részt, illetve a szám hosszát majd argumentumszögét. 
A műveletek menüben (az O vagy az M betű megnyomására) a program kiírja a lehetséges 
opciókat, először a művelet hárombetűs rövidítése a kettő kért érték, a szám azonosítója, kitevő 
(egész szám) vagy kívánt alak. Enter nyomására a program kiírja az új szám azonosítóját, majd a 
szám hosszát és argumentumszögét, ha a kért alak az algebrai alak akkor a valós részt majd a 
képzetes részt. Az S betű hatására a program a szamok.txt-t felülírja és elmenti az aktuálisan 
tárolt számokat, ennek sikerességéről tájékoztat. A Q betű után a program kilép. 
### Programozói dokumentáció 
A program 4 forrásfáljból dolgozik (`main.c`, `beolvasas.c`, `muveletek.c`,
`filekezeles.c`) . A programnak egy fordítóra (compiler, elsősorban gcc) a szabványos 
könyvrakra (stdio.h, math.h, stdlib.h, string.h, stdbool.h) és a saját forrásfáljaira van szüksége. 
A fordítás gcc-vel parancssorból:
```
gcc -c main.c -o main.o 
gcc -c beolvasas.c -o beolvasas.o 
gcc -c muveletek.c -o muveletek.o 
gcc -c filekezeles.c -o filekezeles.o 
gcc main.o beolvasas.o muveletek.o filekezeles.o -o szamologep.exe 
```
Ezután futtatható a `szamologep.exe`. 
A file-ok tartalma és szerepe: 
4 egységre van bontva a főprogram ez csak a főmenüt tartalmazza, a beolvasás ez a beolvasás 
menüt, az ahhoz tartozó függvényeket és a láncolt lista kezeléséhez szükséges függvényeket 
tartalmazza, ezek közül valamelyiket más programrész is használ. A műveletek a műveletek 
menüjét és a hozzátartozó matematikai függvényeket tartalmazza, más programrészek is 
használhatnak innen is párat. Filekezelés, a számokmenésére és beolvasására (txt) használatos 2 
függvény, csak külső meghívásra. 

<b>main.c:</b> 

Ez a főprogram. A számokat dinamikusan láncolt listában tárolja a program a lista elejét (fej, az 
első elemre mutató pointer) a program itt hozza létre, kezdetben NULL. A kilépés funkció (Q) a 
ciklus kilépési felétele, emiatt amig nem akarunk kilépni a menü újra meg újra lefut. A ciklus 
után (ha ki akarunk lépni) van a lista felszabadítása (fv: beolvasás) 

<b>beolvasas.c</b>

A beolvasas.h tartalmazza a struktúrákat. 3 struktúra, egy algebrai alak és kettő trigonometrikus 
alakhoz, az egyik listát épít a másik csak a szám adatait tárolja. Minden szám rendelkezik egy 
azonosítóval (egész szám) ez mindegyik struktúrában megtalálható. A listában a számolás 
0x1a1-től azaz 417-től kezdődik, és mindenhol hexadecimálisan írja ki a program a könnyű 
megkülönböztethetőség érdekében. Az algebrai tárolja a szám valós és egészrészét 
(komplex_algebrai: az, Re, Im), a komplex, ami nem épít listát az a szám hosszát és 
argumentumszögét (komplex_trig: az, r, fi) és ami listát épít az trigonometriai alakban tárolja 
valamint a következő elem pointerét (komplex: az, r, fi, kov). 
A beolvasás menü, amit a főprogram hív meg, valamint a többi függvény a beolvasáshoz és a 
listakezeléshez. A több program számára is elérhető függvények: beolvasás (maga a menü a 
főprogram hívja meg), felszabadítás, hozzáfűzés (a kistához), valamint a teljes lista vagy az 
utolsó elem kiírása. Ez az összes függvény a modulban. 
beolvasas: visszatérési értéke void paramétere: a lista fejére mutató pointer. 
Kiírja a beolvasás menüt, lekezeli a 3 opciót (algebrai, trigonometrikus, file) és ha kell átalakít 
majd meghívja a hozzafuz függvényt hogy a lista végére fűzze a számot. File-ból való 
beolvasásra meghívja a megfelelő függvényt, majd kiírja mindig a teljes új listát. 
felszabait: visszatérési érték: void, paraméter: a lista feje (nem módosítja azt) 
Egyesével végigmegy a lista elemin és felszabadítja azokat. 
kiir és kiirutolso: visszatérési érték: void, paraméter: lista feje (nem módosítja azt). 
mindkettő végigmegy a listán a kiir minden elemet kiír a kiirutolso csak az utolso elemet, 
mindkettő trigonometrikus alakban. 
hozzafuz: visszatérési érték: komplex pointer, azaz a fej, ami lehetséges, hogy változott, 
paraméterei: a fej (visszatérve változtatja, ha kell), a szám hossza (r, valós szám), a szám 
argumentumszöge (fi, valós szám). Lefoglal egy új komplex számnak memóriában helyet, majd 
hossza fűzi a listához, ha a fej NULL (nincs lista) azt módosítja és adja vissza.

<b>muveletek.c</b> 

Tartalmazza a muvelet menüfüggvényt, a műveletek menüjét, a számolófüggvényeket két 
átalakító függvényt, és egy nagybetűbe függvényt. A menüfüggvény, a két átalakító függvény és 
a nagybetűbe függvényt más programrészek is használják. 
muvelet: visszatérési érték: void, paraméter a lista elejére (fej) mutató pointer. 
Kiírja és kezeli a műveletek menüjét. Átalakítja a művelet parancs után kapott 2 paramétert 
számmá, ha kell, és meghívja a műveleti függvényeket, az új számot hozzáírja a listához, és 
kiírja az új számot. 
nagybetube: visszatérési érték: void de a paraméterként cím szerint kapott karaktert, ha kisbetű 
nagybetűssé tesszi és felülírja, ha kisbetű hagyja úgy. 
Átalakítófüggvények: 
Trigonometrikusból algebraiba és vissza. 
Trigonometrikusból algebraiba: trig_to_alg: visszatérési érték: komplex_trig (nem listaelem), 
paraméter egy algebrai alakben megadott szám. 
Algebraiból trigonometrikusba: algebrai_to_trig: visszatérési érték: komplex_algebrai, 
paraméter: egy komplex számra mutató pointer (lista elem). 
Műveleti függvények: 
Mindegyik visszatérési értéke komplex_trig azaz nem listaelem de trigonometriai alak. A 
paraméter két komplex listaelem, kivéve a hatványozásnál és az átalakításnál, ezeknél rendre egy 
egész szám (hatványkitevő) illetve a kívánt alak, karaktertömb. A matematikai műveleteket a 
program mindig a legegyszerűbb alakban végzi, ezért az összeadásnál és a kivonásnál átalakít 
elvégzi a műveletet visszaalakít majd visszatér, a többit trigonometria alakban végzi el.

<b>filekezeles.c</b> 

Két függvényt tartalmaz, mindkettő elérhető más programrészek számára, a filebaírás ás a fileból 
beolvasás. A filebaírás visszatérési értéke logikai változó, jelzi a sikerességet, paraméterként 
átveszi a lista fejét, végigfut és kiír mindent egyesével a szamok.txt file-ba. Az alakot nem 
változóként írja, hanem csak egy T betűt mert minden számot trigonometriai alakban tárol. A 
beolvasás kezeli a két alakot külön. 
beolvasas: visszatérési értél: logikai, a függvény sikerességéről. Paraméter a fejre mutató pointer, 
mert lehetséges, hogy kell változtatni. A függvény soronként beolvas, és kiértékel, ha kell 
(vagyis a szám algebrai alakban van) átalakít, és egyesével hozzáfűzi az elemeket a listához.