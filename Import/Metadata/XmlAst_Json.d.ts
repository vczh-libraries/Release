export type Node = Text | CData | Comment | Element | Instruction | Document;

export interface Text {
    $ast: "Text";
    content: string;
}

export interface CData {
    $ast: "CData";
    content: string;
}

export interface Attribute {
    $ast: "Attribute";
    name: string;
    value: string;
}

export interface Comment {
    $ast: "Comment";
    content: string;
}

export interface Element {
    $ast: "Element";
    name: string;
    closingName: string;
    attributes: (Attribute | null)[];
    subNodes: (Node | null)[];
}

export interface Instruction {
    $ast: "Instruction";
    name: string;
    attributes: (Attribute | null)[];
}

export interface Document {
    $ast: "Document";
    prologs: (Node | null)[];
    rootElement: Element | null;
}

