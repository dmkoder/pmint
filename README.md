# pmj-interpreter
Pmj-interpreter je Interpreter pseudomašinskog jezika razvijen pomoću Flex i GNU Bison tehnologija.

## Struktura

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

**Napomena -** Podržani su isključivo Linux sistemi. Skripta za instalaciju je namenjena isključivo Debian distribucijama, za ostale distribucije neophodno je adekvatno izmeniti skriptu.

Nakon preuzimanja koda, na lokalnoj mašini je poželjno pozicionirati se u direktorijum gde se nalazi `install.sh` skripta. Nakon toga potrebno je kao `sudo` korisnik, iz komandne linije,  izvršiti komandu za dodavanje pristupa izvršavanja skripti i pokrenuti istu.

```
//Dodavanje pristupa install.sh skripti
sudo chmod +x install.sh
//Pokretanje skripte
sudo ./install.sh
```

Skripta za instalaciju će instalirate Flex i Bison koji su neohodni kako bi kod mogao da se kompajlira. Nakon toga kod će biti kompajliran i izvršni fajl će biti prebačen u `/usr/bin/` direktorijum, odakle će biti dostupan svim korisnicima. Nakon toga biće pokrenuto interpretiranje `welcome.txt` fajla u kome se nalazi program napisan u pseudomašinskom jeziku, čiji rezultat treba da bude ispisan.

## Upotreba

Nakon instalacije interpreter se poziva komandom `pmj-interpreter` pod zastavicom `-f` navodi se nayiv fajla u kome se nalazi kod koji treba da bude interpretiran, zastavica `-c` je opciona i služi da prikaže izlaz u boji.

Ako pretpostavim da je kod u fajlu `test.txt` onda se on interpretira na sledeći način:
```
pmj-interpreter -f test.txt -c
```

Izlaz interpretera predstavlja ispis svih memorijskih lokacija u programu.
