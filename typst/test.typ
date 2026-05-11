// ================================
// Typst Starter-Datei
// Wichtige Funktionen in einer Datei
// ================================

// --------------------
// Dokument-Einstellungen
// --------------------
#set page(
  paper: "a4",
  margin: 2cm,
)

#set text(
  font: "Libertinus Serif",
  size: 11pt,
)

#set par(
  justify: true,
  leading: 0.65em,
)

#set heading(numbering: "1.")
#set enum(numbering: "1.")
#set list(marker: [•])

// Eigene Farbe
#let myblue = rgb("2E6BE6")

// Eigene Box-Funktion
#let infobox(title, body) = block(
  fill: luma(240),
  stroke: 1pt + gray,
  inset: 10pt,
  radius: 6pt,
  [
    *#title*  
    #body
  ]
)

// --------------------
// Titel
// --------------------
#align(center)[
  #text(18pt, weight: "bold", fill: myblue)[Typst Starter-Datei]
  \ 
  #text(11pt)[Wichtige Funktionen auf einen Blick]
]

#v(1em)

= Überschriften

== Textformatierung

Normaler Text.

*Fett* 
_Italic_  
#underline[Unterstrichen]  
#strike[Durchgestrichen]  
#text(fill: red)[Roter Text]  
#text(size: 16pt)[Großer Text]

Du kannst auch `inline code` schreiben.

== Absätze und Zeilenumbrüche

Das ist ein normaler Absatz. Typst trennt Absätze durch Leerzeilen.

Das ist ein neuer Absatz.

Ein manueller Zeilenumbruch geht so: \
Hier geht es in der nächsten Zeile weiter.

== Listen

Punktliste:
- Erster Punkt
- Zweiter Punkt
- Dritter Punkt

Nummerierte Liste:
+ Eins
+ Zwei
+ Drei

Verschachtelte Liste:
- Punkt A
  - Unterpunkt A1
  - Unterpunkt A2
- Punkt B

== Zitate

#quote[
  Das ist ein Zitat in Typst.
]

== Mathe

Inline-Mathe: $a^2 + b^2 = c^2$

Block-Mathe:
$
sum_(i=1)^n i = (n(n+1))/2
$

Noch ein Beispiel:
$
f(x) = integral_0^x t^2 dif t
$

== Tabellen

#table(
  columns: 3,
  stroke: 0.5pt + gray,
  inset: 6pt,
  align: center,
  [*Name*], [*Alter*], [*Stadt*],
  [Anna], [21], [Berlin],
  [Ben], [24], [Hamburg],
  [Clara], [19], [München],
)

== Boxen und Layout

#infobox(
  [Hinweis],
  [Das ist eine selbst definierte Box mit `#let`. So kannst du eigene Bausteine bauen.]
)

#v(1em)

#grid(
  columns: (1fr, 1fr),
  gutter: 12pt,
  [
    #rect(
      width: 100%,
      height: 2cm,
      fill: rgb("DDEBFF"),
      radius: 6pt,
    )
  ],
  [
    #rect(
      width: 100%,
      height: 2cm,
      fill: rgb("FFE4CC"),
      radius: 6pt,
    )
  ],
)

== Bilder

Wenn du ein Bild im selben Ordner hast, z. B. `bild.png`:

// #image("bild.png", width: 60%)

Der Code ist auskommentiert, damit die Datei auch ohne Bild funktioniert.

== Code-Blöcke
= Code-Blöcke in Typst

== Einfacher Codeblock

#raw(block: true, "fn main() {\n  println!(\"Hallo Welt!\");\n}")

== Codeblock mit Sprache

#raw(
  block: true,
  lang: "rust",
  "fn main() {\n  println!(\"Hallo Welt!\");\n}"
)

== Python-Beispiel

#raw(
  block: true,
  lang: "python",
  "def hello():
    print('Hallo Welt')"
)

== Inline-Code

Benutze `typst compile main.typ` im Terminal.

== Code in einer Box

#box(
  inset: 8pt,
  stroke: 0.5pt + gray,
  radius: 4pt,
  fill: luma(245),
  raw(
    block: true,
    lang: "bash",
    "typst compile main.typ"
  )
)
= Fibonacci in Typst

#let fib(n) = {
  if n <= 1 {
    n
  } else {
    fib(n - 1) + fib(n - 2)
  }
}

#for i in range(10) [
  fib(#i) = #fib(i) \
]

