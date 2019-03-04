# Goal

* Parsing
  * No need to specify allow ambiguity or not
  * Calculate ambiguous **Parse** cases, pointing out which AST need to support ambiguity
  * Full CFG power, no limitation
  * Error message generation
  * Error recovering
* Serializing
  * Escaping and Unescaping pairs (instead of only unescaping)
  * Calculate ambiguous **ToString** cases
  * Generate **ToString** algorithm
* AST
  * Low overhead AST with reflection
  * Optional creating AST from a pool

# AST Definition (compatible with Workflow)

```
class CLASS_NAME [: BASE_CLASS]
{
  var FIELD_NAME : TYPE;
  ...
}
```

## Configurations

- Include files in generated C++ header
- Depended AST definition files
- Visitors selected to generate
- Optional reflection support

## Types

- `Token`: In the previous version, `Token` is a value type, now it is a reference type.
- `CLASS-NAME`: Another class.
- `TYPE[]`: Array, whose element is not allowed to be another array.

## MISC

- Define a `ToString` algorithm with customizable configurations.

# Lexical Analyzer

- Pair name with regular expressions.
- Extendable tokens.
  - For example, recognize `R"[^\s(]\(` and invoke a callback function to determine the end of the string
- Pair a name with the token subset, and give a default name to a token full set

# Error Messages

- Generate error messages in C++ code

# Syntax Analyzer

- Priority of loops:
  - `+[ RULE ]` means if `RULE` succeeds, skipping `RULE` is not considered even if the rest doesn't parse.
  - `-[ RULE ]` means only if skipping `RULE` makes the clause not able to parse, the result of having RULE is not discarded.
  - `[ RULE ]` means keep both result
  - `+{ RULE }`, `-{ RULE }`, `{ RULE }` are similar, but `{ RULE }` may generate more than two results, meanwhile others only generate one result.
- Being able to change token subset during parsing.
- Being able to specify a error message when a certain action fails.
- Generate SAX-like parser, with a default handler to create AST.

## Supported EBNF

- TOKEN [`:` <PROPERTY-NAME>]
- RULE [`:` <PROPERTY-NAME>]
- Optional:
  - `+[` EBNF `]`
  - `-[` EBNF `]`
  - `[` EBNF `]`
- Loop:
  - `+{` EBNF `}`
  - `-{` EBNF `}`
  - `{` EBNF `}`
- `with{` PROPERTY-ASSIGNMENT ... `}`
 
## EBNF Program

- RULE {`::=` CLAUSE `as` <CLASS-NAME>} `;`
  - Consider a syntax here to switch token set

## ToString Algorithm Requirements
- Every clause should create an AST node. `EXP ::= '(' !EXP ')'` is not allowed, except that this clause has only one node.
- Every rule-name node should be assigned to a property. Token nodes are optional but those properties will be auto-generated.
- Loops cannot be embedded in another loop.
