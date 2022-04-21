# Args Kata

Link zur Kata [hier](https://codingdojo.org/kata/Args/).

## Schritt 1: Schema definieren

Damit der Parser später die gegebenen Strings verifizieren kann muss erst mal eine Syntax für die Schemata festgelegt werden, die unserem Parser sagen, welche Formen der Input haben darf. Das Schema muss für jedes Flag den **Name** und den **Type** enthalten. Mein Schema habe ich so festgelegt, dass immer jeweils in einer Zeile der Name im Format `"-X"`, wobei *X* genau ein Buchstabe sein darf. In der nächsten Zeile steht dann der Value-Type, repräsentiert durch genau einen Buchstaben. es gibt die Typen: 
> i (integer), f (float), b (boolean), n (null/none)  
> für komplexere Typen kann s (string) mit zusätzlichem regulären Ausdruck benutzt werden

Ein Beispielfile **Schema.txt** könnte dann so aussehen:  
-a  
f  
-q  
i  

## Reguläre Ausdrücke

**Reguläre Ausdrücke** sind eine formale Möglichkeit zu definieren, welche Wörter von einer Grammatik akzeptiert werden. Das kann für uns sehr hilfreich sein. Zusätzlich können wir damit alle noch so komplizierten Arten von Input beschreiben. Reguläre Ausdrücke sehen so aus:  
`(a-z | 0-9)* @ (a-z)* \. (a-z)*`  

> (x)* : Beliebige Anzahl an x-en auch 0  
> (x)+ : Beliebige Anzahl an x-en nicht 0  
> [x]    : Optionales Zeichen  

Falls du Reguläre Ausdrücke noch nicht kennst hier eine einfache [Erklärung](https://regexr.com/).  
Die tatsächliche Syntax kann sich je nach Implementierung unterscheiden. (C++ benutzt standardmäßig [ECMA-Script](https://www.cplusplus.com/reference/regex/ECMAScript/))

# Umsetzung

**Es ist sehr hilfreich die Funktionen die ganze Zeit ausgiebig zu testen, da es sehr viele verschiedene Kombinationen zu beachten gibt. Sinnvolle Fehlermeldungen sind dabei genauso wichtig!**

## Schritt 2: Schema Parser 

Zuerst brauchen wir eine Parser, der das Schema-file einlesen kann und uns die verschiedenen Flags gut formatiert ablegt. Der Parser sollte erst überprüfen, ob der **Name** des Flags das korrekte Format hat, dann ob es einen gültigen **Typ** hat und beides danach in einem Vector ablegen. In der Lösung machen dass die Funktionen: `bool CheckFlagName(string name)` und `bool CheckFlagValue(string name)`. Um die Flags des Schemas zu speichern bietet es sich an einen Vektor zu verwenden.

## Schritt 3: Command Parser

Als nächstes brauchen wir natürlich den Parser, der die eigentlichen Kommandos bekommt und diese auf die Gültigkeit überprüft. Dieser sollte ähnlich dem Schema Parser zuerst Überprüfen, ob der Name des Flags in dem Schema vorgesehen ist und danach ob der Type richtig ist. Bei mir sind das die Funktionen, `auto CheckFlagName(const vector<string>&vec,string flag)` und `bool CheckFlagValueType(string entry,string& value)`. Da für unterschiedliche Typen unterschiedliche Formate möglich sind, habe ich die Individuellen Überprüfungen in eigene Funktionen mit der Signatur `TYPE CheckForTYPE(string flag)` ausgelagert. Diese können auch später wiederverwendet werden, um den Wert des Flags zu bekommen. Nach der Überprüfung sollten die Werte wieder in einem Vector gespeichert werden.  
*Beachte: falls für ein Flag kein Wert angegeben wurde soll ein geeigneter Default-Wert ausgegeben werden.*

## Schritt 4: Werte Abrufen

Als letztes muss es noch eine Möglichkeit geben, die gespeicherten Werte abzufragen. Dafür bieten sich Template-Funktionen an, die die vorherige `TYPE CheckForTYPE(string flag)` Funktion nutzen um den Wert des entsprechenden Flags auszugeben. Bei mir sind das die Template-Spezialisierungen mit der Signatur: `template<class Type> Type GetFlag(string flag)`. Im Prinzip muss man bei allen drei Vorgängen, ähnliche Schritte durchgehen.

