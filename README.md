# pmj-interpreter
Pmj-interpreter je Interpreter pseudomašinskog jezika razvijen pomoću Flex i GNU Bison tehnologija.

## Struktura
```
+ pmj-interpreter/
  + headerFiles/
    - engine.h
    - macros.h
    - structs.h
  - install.sh
  - lex.l
  - readme.md
  - welcome.txt
  - yacc.y
```

## Instrukcije
Postoje tri osnovne grupe instrukcija:
1. Instrukcije obrade
  - Aritmetičke operacije nad realnim brojevima
  - Aritmetičke operacije nad celim brojevima
  - Logičke operacije
  - Operacije pomeranja sadržaja registra
2. Instrukcije prenošenja
  - Instrukcije za komunikaciju između memorijskih registara i akumulatora
3. Instrukcije upravljanja 
  - Instrukcije uslovnog skoka
  - Instrukcije bezuslovnog skoka
  - Instrukcije prestanka rada

```
Heksadekadni kod |Mnemotehnička oznaka |Artesni deo |Fuknkcija         |Komentar
01               |SAB                  |R           |S(AK) + S(R)→AK   |Aritmetičke 
02               |ODU                  |R           |S(AK) - S(R)→AK   |operacija 
03               |MNO                  |R           |S(AK) * S(R)→AK   |u 
04               |DEL                  |R           |S(AK) / S(R)→AK   |pokretnom 
05               |PZA                  |R           |-S(AK) → AK       |zarezu
11               |SABF                 |R           |S(AK) + S(R)→AK   |Aritmetičke 
12               |ODUF                 |R           |S(AK) - S(R)→AK   |operacije 
13               |MNOF                 |R           |S(AK) * S(R)→AK   |u 
14               |DELF                 |R           |S(AK) / S(R)→AK   |fiksnom 
15               |PZAF                 |R           |-S(AK) → AK       |zarezu
21               |KON                  |R           |S(AK) Ʌ S(R)→AK   |Logičke  
22               |DIS                  |R           |S(AK) V S(R)→AK   |operacije
23               |NEG                  |            |-S(AK)→AK         |
31               |POL                  |R           |Улево R пута      |Linijsko
32               |POD                  |R           |Удесно R пута     |pomeranje
41               |MUA                  |R           |S(R) → AK         |Prenošenje
42               |AUM                  |R           |S(AK) → S(R)      |
51               |NES                  |R           |S(AK)<0, R→BI     |Uslovni skok
52               |NUS                  |R           |S(AK)=0, R→BI     |
53               |BES                  |R           |R→BI              |Bezuslovni skok
54               |ZAR                  |R           |                  |Završavanje
```
Pseudomašinska instrukcija za rezervisanje memorijskih lokacija je DM \<Ceo broj\>.

Pseudomašinske instrukcije za definisanje podataka:
 - DC \<Lista celih brojeva\>
 - DR \<Lista realnih brojeva\>
 - DZ \<Znakovni podatak\>

Mogući načini adresiranja jesu:
 - Direktno adresiranje
 - Indeksno adresiranje
 - Relativno adresiranje
 - Indirektno adresiranje
 - Neposredno adresiranje

## Instalacija

1. Pre same instalacije neophodno je instalirati Flex i Bison. Na sistemima Debian distribucije (Ubuntu) ovo je moguce uraditi komandom:
```
sudo apt install flex bison
```
2. Sledeci korak jeste preuzimanje git repozitorijuma. Moguće je skinuti ručno repozitorijum u obliku .zip fajla, ili iz komandne linije komandom:
```
git clone https://github.com/dmkoder/pmint.git
```
3. Nakon toga pozicionirajte se u root direktorijum kloniranog projekta i izvršite komandu make iz komandne linije:
```
make
```
4. Rezultat komande make će biti ```mpint``` izvršni fajl. Kako bi izvršni fajl bio svima dostupan premestite ga u ```/usr/bin/``` direktorijum komandom.

```
mv pmint /usr/bin/
```

5.) Testirajte program (u istom direktorijumu) komandom:
```
pmint -f welcome.txt -c
```


## Upotreba

Nakon instalacije interpreter se poziva komandom `pmj-interpreter`, pod zastavicom `-f` navodi se naziv fajla u kome se nalazi kod koji treba da bude interpretiran, zastavica `-c` je opciona i služi da prikaže izlaz u boji.

Ako pretpostavim da je kod u fajlu `test.txt` onda se on interpretira na sledeći način:
```
pmj-interpreter -f test.txt -c
```

Izlaz interpretera predstavlja ispis svih memorijskih lokacija u programu.
