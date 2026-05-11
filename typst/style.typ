// ========================================
// style.typ
// Typst-Style ähnlich zu deinem LaTeX-Paket
// ========================================

// -----------------------------
// Grundlayout
// -----------------------------
#set page(
  paper: "a4",
  margin: 2cm,
  footer: context align(center)[#counter(page).display()],
)

#set text(
  font: "Latin Modern Sans",
  size: 11pt,
  fill: rgb("#222222"),
)

#set par(
  justify: false,
  leading: 0.65em,
)

#show par: it => block(
  spacing: 0.9em,
  it,
)

// -----------------------------
// Überschriften
// -----------------------------
#set heading(numbering: "1.")

#show heading.where(level: 1): it => {
  let num = if it.numbering != none { it.numbering + h(0.6em) } else { [] }
  block(
    above: 15pt,
    below: 0pt,
    text(17pt, weight: "bold", fill: rgb("#222222"))[
      #num #it.body
    ],
  )
}

#show heading.where(level: 2): it => {
  let num = if it.numbering != none { it.numbering + h(0.6em) } else { [] }
  block(
    above: 10pt,
    below: 0pt,
    text(14pt, weight: "bold", fill: rgb("#222222"))[
      #num #it.body
    ],
  )
}

#show heading.where(level: 3): it => {
  let num = if it.numbering != none { it.numbering + h(0.6em) } else { [] }
  block(
    above: 5pt,
    below: 0pt,
    text(11pt, weight: "bold", fill: rgb("#222222"))[
      #num #it.body
    ],
  )
}


// -----------------------------
// Listen
// -----------------------------
#set enum(
  numbering: "1.",
  indent: 1.1em,
)

#set list(
  indent: 1.6em,
  body-indent: 0.8em,
)


// -----------------------------
// Titelfunktion
// Entspricht ungefähr \stdtitle
// -----------------------------
#let stdtitle(line1, line2, line3) = {
  align(center)[
    #text(18pt, weight: "bold", fill: rgb("#222222"))[#line1] \
    #text(18pt, weight: "bold", fill: rgb("#222222"))[#line2] \
    #text(14pt, weight: "bold", fill: rgb("#222222"))[#line3]
  ]
  v(10pt)
}


// -----------------------------
// Hilfsfunktionen für Textstil
// -----------------------------
#let titlefont(body) = text(
  font: "Latin Modern Sans",
  weight: "bold",
  fill: rgb("#222222"),
)[#body]

#let dul(body) = underline(underline(body))


// -----------------------------
// Mathe-Makros
// Nutzung: $#R$, $#Hom(V, W)$ usw.
// -----------------------------

// Mengen
#let SET(a, b) = math.lr("{", a + " | " + b, "}")
#let Set(x) = math.lr("{", x, "}")

// Standardräume
#let R = math.bb("R")
#let C = math.bb("C")
#let Q = math.bb("Q")
#let Z = math.bb("Z")
#let N = math.bb("N")

// Operatoren
#let id = math.op("id")
#let Image = math.op("Im")
#let rank = math.op("rank")
#let Hom = math.op("Hom")
#let Span = math.op("span")
#let mol = math.op("mol")

// Griechische Kurzformen
#let dlt = math.delta
#let eps = math.epsilon.alt

// Quantoren
#let fa = math.forall
#let ex = math.exists
#let nex = math.exists.not

// Delimiter
#let ceil(x) = math.ceil(x)
#let floor(x) = math.floor(x)
#let abs(x) = math.abs(x)
#let norm(x) = math.norm(x)


// -----------------------------
// Kleine Box für wichtige Hinweise
// optional, aber praktisch
// -----------------------------
#let infobox(body) = block(
  fill: luma(245),
  stroke: 0.6pt + gray,
  inset: 10pt,
  radius: 4pt,
  body,
)