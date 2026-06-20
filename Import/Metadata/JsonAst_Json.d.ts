export type LiteralValue = "True" | "False" | "Null";

export type Node = Literal | String | Number | Array | Object;

export interface Literal {
    $ast: "Literal";
    value: LiteralValue;
}

export interface String {
    $ast: "String";
    content: string;
}

export interface Number {
    $ast: "Number";
    content: string;
}

export interface Array {
    $ast: "Array";
    items: (Node | null)[];
}

export interface ObjectField {
    $ast: "ObjectField";
    name: string;
    value: Node | null;
}

export interface Object {
    $ast: "Object";
    fields: (ObjectField | null)[];
}

