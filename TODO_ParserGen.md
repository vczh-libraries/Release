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

- TOKEN [`:` PROPERTY-NAME]
- RULE [`:` PROPERTY-NAME]
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

- RULE {`::=` CLAUSE `as` CLASS-NAME} `;`
  - Consider a syntax here to switch token set

## ToString Algorithm Requirements
- Every clause should create an AST node. `EXP ::= '(' !EXP ')'` is not allowed, except that this clause has only one node.
- Every rule-name node should be assigned to a property. Token nodes are optional but those properties will be auto-generated.
- Loops cannot be embedded in another loop. It doesn't limit the syntax, but it limit the shape of AST.

## Development Project Structure
- Original ParserGen code will be separated from Vlpp.
- **AstGen**:
  - AST symbols and C++ code generation.
  - Generate visitors.
  - Generate easy builder.
  - Generate reflection.
  - Symbol serialization (this is not exposed on the final ParserGen.exe)
- **Execution**:
  - Parser-generated instructions serialization.
  - Execute instructions as a SAX-like parser, with notification on ambigious node, error message generation and error recovering.
- **Compiler**: depends on **AstGen** and **Execution**, taking the generated `AST for ParserGen`.
  - Take the `AST for ParserGen` and generate instructions.
  - Generate the default handler to create AST for the SAX-like parser.
  - ToString algorithm
- **ParserGen**: depends on **Compiler**, taking the generated parser and the default handler to create AST for `AST for ParserGen`.
  - All code integrating together.
- **UnitTestAst**:
  - Unit test of **AstGen** building block and pool allocation etc.
  - Hand-written `AST for ParserGen` symbols and codegen it, with all visitors and the easy builder.
- **UnitTestExecution**:
  - Unit test of **Execution**.
  - Assert directly on SAX-like parser.
- **UnitTestCompiler**:
  - Unit test of **Compiler**, input are all **UnitTestExecution** test cases rewritten using the generated easy-builder for `AST for ParserGen` AST.
  - Assert on the ToString-ed AST. (shared)
  - One of the test case will take the syntax of `AST for ParserGen` itself, with the symbol directly for the AST, and serialize instructions to a cpp file, so that we create a parser in C++ to parse the input of the ParserGen.
- **UnitTestParserGen**:
  - Unit test of **ParserGen**, input are all **UnitTestExecution** test cases rewritten in text format.
  - Assert on the ToString-ed AST. (shared)
  - Generate all parser in text format to C++ code
- **UnitTest**:
  - Link all cpp files in all other unit test projects so that all test cases can be run in one F5.
  - Test all generated parsers in **UnitTestParserGen**.
  - Assert on the ToString-ed AST. (shared)
- Since parser are written in different ways for different unit test projects, they are stored separately from unit test projects to share necessary files.
- Do not really write a file if the generated content doesn't change.
