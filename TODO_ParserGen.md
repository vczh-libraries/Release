* Parsing
    * No need to specify allow ambiguity or not
    * Calculate ambiguous **Parse** cases, pointing out which AST need to support ambiguity
    * Full CFG power, no limitation
    * Be able to assign to any properties (not just enum) in with statement
    * Error message generation
    * Error recovering
* Serializing
    * Escaping and Unescaping pairs (instead of only unescaping)
    * Calculate ambiguous **ToString** cases
    * Generate **ToString** algorithm
* AST
    * Low overhead AST with reflection
