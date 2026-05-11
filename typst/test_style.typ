#import "style.typ": *

#stdtitle(
  [Analysis],
  [Zusammenfassung],
  [Frühjahrssemester 2026],
)

= Grundlagen

Das ist ein Beispieltext im Stil deiner alten LaTeX-Vorlage.

Die Schrift ist serifenlos, der Text linksbündig, mit etwas größerem Zeilenabstand.

== Mengen und Zahlenbereiche

Wir arbeiten über $#R$, manchmal auch über $#C$, $#Q$, $#Z$ und $#N$.

Ein Beispiel für eine Menge:
$
A = { x in #R | x > 0 }
$

Oder kurz:
$
B = #Set("1, 2, 3")
$

== Lineare Algebra

Sei $T: #R^n -> #R^m$ eine lineare Abbildung.

Dann gilt:
$
#Image (T) subset.eq #R^m
$

und
$
#rank (T) <= n
$

Außerdem betrachten wir
$
#Hom (V, W)
$
und den Unterraum
$
#Span (v_1, v_2, v_3).
$

== Quantoren 
\
Es gilt:
$
#fa x in #R: x^2 >= 0
$

Außerdem:
$
#ex x in #R: x^2 = 2
$

Und:
$
#nex x in #R: x^2 = -1
$

== Beträge und Normen

$
#abs("x-y")
$

$
#norm("v")
$

$
#ceil("x/2"), quad #floor("x/2")
$

== Listen

+ Erster Punkt
+ Zweiter Punkt
+ Dritter Punkt

- Ein Stichpunkt
- Noch ein Stichpunkt

== Hervorhebung

#dul[Wichtiger Begriff]

== Display-Mathe

$
sum_(k=1)^n k = frac(n(n+1), 2)
$

$
integral_0^1 x^2 dif x = 1 / 3
$

== Hinweisbox

#infobox[
Das ist eine optionale Box. So etwas ersetzt in Typst oft kleine LaTeX-Konstruktionen sehr elegant.
]

== Codeblock

#raw(
  block: true,
  lang: "bash",
  "typst compile main.typ"
)