# Knihovna Sparse Matrix

Knihovna Sparse Matrix implementuje řídkou matici za využití formátu [CSR](http://netlib.org/linalg/html_templates/node91.html#SECTION00931100000000000000). Její použití by mělo být maximálně intuitivní (vizte příklady níže).

## Použití

### Vytvoření matice

Konstruktor přebírá jeden či dva parametry v závislosti na tom, chceme-li vytvořit čtvercovou, resp. nečtvercovou matici.

```cpp
SparseMatrix a(3); // matice 3×3
SparseMatrix b(3, 5); // matice 3×5 (3 řádky, 5 sloupců)
```


### Maticové operace

#### Vložení prvku

Pro vložení prvku použijeme metodu `insert()`, které řekneme, co a kam chceme vložit.

```cpp
SparseMatrix a(3);
a.insert(-5, 2, 3); // vloží hodnotu -5 na 2. řádek do 3. sloupce
```

#### Čtení prvku

Pro přečtení prvku použijeme metodu `get()`, které předáme souřadnice čteného prvku.

```cpp
SparseMatrix a(3);
a.get(2, 3); // vrátí hodnotu prvku na 2. řádku ve 3. sloupci (vrátí 0, pokud na tuto pozici nebyl vložen prvek)
```

#### Násobení vektorem

Při dodržení správných rozměrů můžeme matici přenásobit vektorem zprava.

```cpp
SparseMatrix a(3);
vector<int> x(3, 2);
a.multiply(x);
```

#### Násobení maticí

Opětovně při dodržení správných rozměrů můžeme matici přenásobit jinou maticí zprava.

```cpp
SparseMatrix a(3, 4);
SparseMatrix b(4, 5);
SparseMatrix result = a.multiply(b);
```

#### Součet matic

Pokud mají 2 matice stejné rozměry, můžeme je sečíst.

```cpp
SparseMatrix a(3, 4);
SparseMatrix b(3, 4);
SparseMatrix result = a.add(b);
```
