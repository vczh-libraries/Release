export type FunctionKind = "Static" | "Override" | "Normal";

export type PredefinedTypeName = "Void" | "Object" | "Interface" | "Int" | "UInt" | "Float" | "Double" | "String" | "Char" | "Bool";

export type MapWritability = "Readonly" | "Writable";

export type FunctionAnonymity = "Named" | "Anonymous";

export type ClassKind = "Class" | "Interface";

export type ConstructorType = "Undefined" | "SharedPtr" | "RawPtr";

export type EnumKind = "Normal" | "Flag";

export type EnumItemKind = "Constant" | "Intersection";

export type APConst = "Readonly" | "Writable";

export type APObserve = "Observable" | "NotObservable";

export type ForEachDirection = "Normal" | "Reversed";

export type StateSwitchType = "Default" | "Pass" | "PassAndReturn" | "Ignore" | "IgnoreAndReturn";

export type StateInvokeType = "Goto" | "Push";

export type LiteralValue = "Null" | "True" | "False";

export type UnaryOperator = "Positive" | "Negative" | "Not";

export type BinaryOperator = "Assign" | "Index" | "FlagAnd" | "FlagOr" | "FailedThen" | "Exp" | "Add" | "Sub" | "Mul" | "Div" | "Mod" | "Shl" | "Shr" | "LT" | "GT" | "LE" | "GE" | "EQ" | "NE" | "Xor" | "And" | "Or";

export type RangeBoundary = "Inclusive" | "Exclusive";

export type SetTesting = "In" | "NotIn";

export type TypeCastingStrategy = "Strong" | "Weak";

export type TypeTesting = "IsType" | "IsNotType" | "IsNull" | "IsNotNull";

export type ObserveType = "SimpleObserve" | "ExtendedObserve";

export type ModuleType = "Module" | "Unit";

export type Type = PredefinedType | TopQualifiedType | ReferenceType | RawPointerType | SharedPointerType | NullableType | EnumerableType | MapType | ObservableListType | FunctionType | ChildType;

export type Expression = ThisExpression | TopQualifiedExpression | ReferenceExpression | OrderedNameExpression | OrderedLambdaExpression | MemberExpression | ChildExpression | LiteralExpression | FloatingExpression | IntegerExpression | StringExpression | UnaryExpression | BinaryExpression | LetExpression | IfExpression | RangeExpression | SetTestingExpression | ConstructorExpression | InferExpression | TypeCastingExpression | TypeTestingExpression | TypeOfTypeExpression | TypeOfExpressionExpression | AttachEventExpression | DetachEventExpression | ObserveExpression | CallExpression | FunctionExpression | NewClassExpression | NewInterfaceExpression | FormatExpression | BindExpression | NewCoroutineExpression | MixinCastExpression | ExpectedTypeCastExpression | CoOperatorExpression;

export type Statement = BreakStatement | ContinueStatement | ReturnStatement | DeleteStatement | RaiseExceptionStatement | IfStatement | WhileStatement | TryStatement | BlockStatement | GotoStatement | VariableStatement | ExpressionStatement | ForEachStatement | SwitchStatement | CoProviderStatement | CoPauseStatement | CoOperatorStatement | StateSwitchStatement | StateInvokeStatement;

export type Declaration = NamespaceDeclaration | FunctionDeclaration | VariableDeclaration | EventDeclaration | PropertyDeclaration | StaticInitDeclaration | ConstructorDeclaration | DestructorDeclaration | ClassDeclaration | EnumDeclaration | StructDeclaration | AutoPropertyDeclaration | CastResultInterfaceDeclaration | StateMachineDeclaration;

export type VirtualCfeDeclaration = AutoPropertyDeclaration | CastResultInterfaceDeclaration;

export type VirtualCseDeclaration = StateMachineDeclaration;

export type VirtualCseStatement = ForEachStatement | SwitchStatement | CoProviderStatement;

export type CoroutineStatement = CoPauseStatement | CoOperatorStatement;

export type StateMachineStatement = StateSwitchStatement | StateInvokeStatement;

export type VirtualCfeExpression = FormatExpression;

export type VirtualCseExpression = BindExpression | NewCoroutineExpression | MixinCastExpression | ExpectedTypeCastExpression | CoOperatorExpression;

export type ModuleUsingFragment = ModuleUsingNameFragment | ModuleUsingWildCardFragment;

export interface Declaration_Common {
    attributes: (Attribute | null)[];
    name: string;
}

export interface VirtualCfeDeclaration_Common extends Declaration_Common {
    expandedDeclarations: (Declaration | null)[];
}

export interface VirtualCseDeclaration_Common extends Declaration_Common {
    expandedDeclarations: (Declaration | null)[];
}

export interface VirtualCseStatement_Common {
    expandedStatement: Statement | null;
}

export interface VirtualCfeExpression_Common {
    expandedExpression: Expression | null;
}

export interface VirtualCseExpression_Common {
    expandedExpression: Expression | null;
}

export interface Attribute {
    $ast: "Attribute";
    category: string;
    name: string;
    value: Expression | null;
}

export interface PredefinedType {
    $ast: "PredefinedType";
    name: PredefinedTypeName;
}

export interface TopQualifiedType {
    $ast: "TopQualifiedType";
    name: string;
}

export interface ReferenceType {
    $ast: "ReferenceType";
    name: string;
}

export interface RawPointerType {
    $ast: "RawPointerType";
    element: Type | null;
}

export interface SharedPointerType {
    $ast: "SharedPointerType";
    element: Type | null;
}

export interface NullableType {
    $ast: "NullableType";
    element: Type | null;
}

export interface EnumerableType {
    $ast: "EnumerableType";
    element: Type | null;
}

export interface MapType {
    $ast: "MapType";
    writability: MapWritability;
    key: Type | null;
    value: Type | null;
}

export interface ObservableListType {
    $ast: "ObservableListType";
    element: Type | null;
}

export interface FunctionType {
    $ast: "FunctionType";
    result: Type | null;
    arguments: (Type | null)[];
}

export interface ChildType {
    $ast: "ChildType";
    parent: Type | null;
    name: string;
}

export interface NamespaceDeclaration extends Declaration_Common {
    $ast: "NamespaceDeclaration";
    declarations: (Declaration | null)[];
}

export interface FunctionArgument {
    $ast: "FunctionArgument";
    attributes: (Attribute | null)[];
    name: string;
    type: Type | null;
}

export interface FunctionDeclaration extends Declaration_Common {
    $ast: "FunctionDeclaration";
    functionKind: FunctionKind;
    anonymity: FunctionAnonymity;
    arguments: (FunctionArgument | null)[];
    returnType: Type | null;
    statement: Statement | null;
}

export interface VariableDeclaration extends Declaration_Common {
    $ast: "VariableDeclaration";
    type: Type | null;
    expression: Expression | null;
}

export interface EventDeclaration extends Declaration_Common {
    $ast: "EventDeclaration";
    arguments: (Type | null)[];
}

export interface PropertyDeclaration extends Declaration_Common {
    $ast: "PropertyDeclaration";
    type: Type | null;
    getter: string;
    setter: string;
    valueChangedEvent: string;
}

export interface StaticInitDeclaration extends Declaration_Common {
    $ast: "StaticInitDeclaration";
    statement: Statement | null;
}

export interface BaseConstructorCall {
    $ast: "BaseConstructorCall";
    type: Type | null;
    arguments: (Expression | null)[];
}

export interface ConstructorDeclaration extends Declaration_Common {
    $ast: "ConstructorDeclaration";
    constructorType: ConstructorType;
    baseConstructorCalls: (BaseConstructorCall | null)[];
    arguments: (FunctionArgument | null)[];
    statement: Statement | null;
}

export interface DestructorDeclaration extends Declaration_Common {
    $ast: "DestructorDeclaration";
    statement: Statement | null;
}

export interface ClassDeclaration extends Declaration_Common {
    $ast: "ClassDeclaration";
    kind: ClassKind;
    constructorType: ConstructorType;
    baseTypes: (Type | null)[];
    declarations: (Declaration | null)[];
}

export interface EnumItemIntersection {
    $ast: "EnumItemIntersection";
    name: string;
}

export interface EnumItem {
    $ast: "EnumItem";
    attributes: (Attribute | null)[];
    name: string;
    kind: EnumItemKind;
    number: string;
    intersections: (EnumItemIntersection | null)[];
}

export interface EnumDeclaration extends Declaration_Common {
    $ast: "EnumDeclaration";
    kind: EnumKind;
    items: (EnumItem | null)[];
}

export interface StructMember {
    $ast: "StructMember";
    attributes: (Attribute | null)[];
    name: string;
    type: Type | null;
}

export interface StructDeclaration extends Declaration_Common {
    $ast: "StructDeclaration";
    members: (StructMember | null)[];
}

export interface AutoPropertyDeclaration extends VirtualCfeDeclaration_Common {
    $ast: "AutoPropertyDeclaration";
    functionKind: FunctionKind;
    type: Type | null;
    configConst: APConst;
    configObserve: APObserve;
    expression: Expression | null;
}

export interface CastResultInterfaceDeclaration extends VirtualCfeDeclaration_Common {
    $ast: "CastResultInterfaceDeclaration";
    baseType: Type | null;
    elementType: Type | null;
}

export interface StateInput {
    $ast: "StateInput";
    name: string;
    arguments: (FunctionArgument | null)[];
}

export interface StateDeclaration {
    $ast: "StateDeclaration";
    name: string;
    arguments: (FunctionArgument | null)[];
    statement: Statement | null;
}

export interface StateMachineDeclaration extends VirtualCseDeclaration_Common {
    $ast: "StateMachineDeclaration";
    inputs: (StateInput | null)[];
    states: (StateDeclaration | null)[];
}

export interface BreakStatement {
    $ast: "BreakStatement";
}

export interface ContinueStatement {
    $ast: "ContinueStatement";
}

export interface ReturnStatement {
    $ast: "ReturnStatement";
    expression: Expression | null;
}

export interface DeleteStatement {
    $ast: "DeleteStatement";
    expression: Expression | null;
}

export interface RaiseExceptionStatement {
    $ast: "RaiseExceptionStatement";
    expression: Expression | null;
}

export interface IfStatement {
    $ast: "IfStatement";
    type: Type | null;
    name: string;
    expression: Expression | null;
    trueBranch: Statement | null;
    falseBranch: Statement | null;
}

export interface WhileStatement {
    $ast: "WhileStatement";
    condition: Expression | null;
    statement: Statement | null;
}

export interface TryStatement {
    $ast: "TryStatement";
    protectedStatement: Statement | null;
    name: string;
    catchStatement: Statement | null;
    finallyStatement: Statement | null;
}

export interface BlockStatement {
    $ast: "BlockStatement";
    statements: (Statement | null)[];
    endLabel: string;
}

export interface GotoStatement {
    $ast: "GotoStatement";
    label: string;
}

export interface VariableStatement {
    $ast: "VariableStatement";
    variable: VariableDeclaration | null;
}

export interface ExpressionStatement {
    $ast: "ExpressionStatement";
    expression: Expression | null;
}

export interface ForEachStatement extends VirtualCseStatement_Common {
    $ast: "ForEachStatement";
    name: string;
    direction: ForEachDirection;
    collection: Expression | null;
    statement: Statement | null;
}

export interface SwitchCase {
    $ast: "SwitchCase";
    expression: Expression | null;
    statement: Statement | null;
}

export interface SwitchStatement extends VirtualCseStatement_Common {
    $ast: "SwitchStatement";
    expression: Expression | null;
    caseBranches: (SwitchCase | null)[];
    defaultBranch: Statement | null;
}

export interface CoProviderStatement extends VirtualCseStatement_Common {
    $ast: "CoProviderStatement";
    name: string;
    statement: Statement | null;
}

export interface CoPauseStatement {
    $ast: "CoPauseStatement";
    statement: Statement | null;
}

export interface CoOperatorStatement {
    $ast: "CoOperatorStatement";
    varName: string;
    opName: string;
    arguments: (Expression | null)[];
}

export interface StateSwitchArgument {
    $ast: "StateSwitchArgument";
    name: string;
}

export interface StateSwitchCase {
    $ast: "StateSwitchCase";
    name: string;
    arguments: (StateSwitchArgument | null)[];
    statement: Statement | null;
}

export interface StateSwitchStatement {
    $ast: "StateSwitchStatement";
    type: StateSwitchType;
    caseBranches: (StateSwitchCase | null)[];
}

export interface StateInvokeStatement {
    $ast: "StateInvokeStatement";
    type: StateInvokeType;
    name: string;
    arguments: (Expression | null)[];
}

export interface ThisExpression {
    $ast: "ThisExpression";
}

export interface TopQualifiedExpression {
    $ast: "TopQualifiedExpression";
    name: string;
}

export interface ReferenceExpression {
    $ast: "ReferenceExpression";
    name: string;
}

export interface OrderedNameExpression {
    $ast: "OrderedNameExpression";
    name: string;
}

export interface OrderedLambdaExpression {
    $ast: "OrderedLambdaExpression";
    body: Expression | null;
}

export interface MemberExpression {
    $ast: "MemberExpression";
    parent: Expression | null;
    name: string;
}

export interface ChildExpression {
    $ast: "ChildExpression";
    parent: Expression | null;
    name: string;
}

export interface LiteralExpression {
    $ast: "LiteralExpression";
    value: LiteralValue;
}

export interface FloatingExpression {
    $ast: "FloatingExpression";
    value: string;
}

export interface IntegerExpression {
    $ast: "IntegerExpression";
    value: string;
}

export interface StringExpression {
    $ast: "StringExpression";
    value: string;
}

export interface UnaryExpression {
    $ast: "UnaryExpression";
    op: UnaryOperator;
    operand: Expression | null;
}

export interface BinaryExpression {
    $ast: "BinaryExpression";
    op: BinaryOperator;
    first: Expression | null;
    second: Expression | null;
}

export interface LetVariable {
    $ast: "LetVariable";
    name: string;
    value: Expression | null;
}

export interface LetExpression {
    $ast: "LetExpression";
    variables: (LetVariable | null)[];
    expression: Expression | null;
}

export interface IfExpression {
    $ast: "IfExpression";
    condition: Expression | null;
    trueBranch: Expression | null;
    falseBranch: Expression | null;
}

export interface RangeExpression {
    $ast: "RangeExpression";
    begin: Expression | null;
    beginBoundary: RangeBoundary;
    end: Expression | null;
    endBoundary: RangeBoundary;
}

export interface SetTestingExpression {
    $ast: "SetTestingExpression";
    test: SetTesting;
    element: Expression | null;
    collection: Expression | null;
}

export interface ConstructorArgument {
    $ast: "ConstructorArgument";
    key: Expression | null;
    value: Expression | null;
}

export interface ConstructorExpression {
    $ast: "ConstructorExpression";
    arguments: (ConstructorArgument | null)[];
}

export interface InferExpression {
    $ast: "InferExpression";
    expression: Expression | null;
    type: Type | null;
}

export interface TypeCastingExpression {
    $ast: "TypeCastingExpression";
    strategy: TypeCastingStrategy;
    expression: Expression | null;
    type: Type | null;
}

export interface TypeTestingExpression {
    $ast: "TypeTestingExpression";
    test: TypeTesting;
    expression: Expression | null;
    type: Type | null;
}

export interface TypeOfTypeExpression {
    $ast: "TypeOfTypeExpression";
    type: Type | null;
}

export interface TypeOfExpressionExpression {
    $ast: "TypeOfExpressionExpression";
    expression: Expression | null;
}

export interface AttachEventExpression {
    $ast: "AttachEventExpression";
    event: Expression | null;
    function: Expression | null;
}

export interface DetachEventExpression {
    $ast: "DetachEventExpression";
    event: Expression | null;
    handler: Expression | null;
}

export interface ObserveExpression {
    $ast: "ObserveExpression";
    parent: Expression | null;
    observeType: ObserveType;
    name: string;
    expression: Expression | null;
    events: (Expression | null)[];
}

export interface CallExpression {
    $ast: "CallExpression";
    function: Expression | null;
    arguments: (Expression | null)[];
}

export interface FunctionExpression {
    $ast: "FunctionExpression";
    function: FunctionDeclaration | null;
}

export interface NewClassExpression {
    $ast: "NewClassExpression";
    type: Type | null;
    arguments: (Expression | null)[];
}

export interface NewInterfaceExpression {
    $ast: "NewInterfaceExpression";
    type: Type | null;
    declarations: (Declaration | null)[];
}

export interface FormatExpression extends VirtualCfeExpression_Common {
    $ast: "FormatExpression";
    value: string;
}

export interface BindExpression extends VirtualCseExpression_Common {
    $ast: "BindExpression";
    expression: Expression | null;
}

export interface NewCoroutineExpression extends VirtualCseExpression_Common {
    $ast: "NewCoroutineExpression";
    name: string;
    statement: Statement | null;
}

export interface MixinCastExpression extends VirtualCseExpression_Common {
    $ast: "MixinCastExpression";
    type: Type | null;
    expression: Expression | null;
}

export interface ExpectedTypeCastExpression extends VirtualCseExpression_Common {
    $ast: "ExpectedTypeCastExpression";
    strategy: TypeCastingStrategy;
    expression: Expression | null;
}

export interface CoOperatorExpression extends VirtualCseExpression_Common {
    $ast: "CoOperatorExpression";
    name: string;
}

export interface ModuleUsingNameFragment {
    $ast: "ModuleUsingNameFragment";
    name: string;
}

export interface ModuleUsingWildCardFragment {
    $ast: "ModuleUsingWildCardFragment";
}

export interface ModuleUsingItem {
    $ast: "ModuleUsingItem";
    fragments: (ModuleUsingFragment | null)[];
}

export interface ModuleUsingPath {
    $ast: "ModuleUsingPath";
    items: (ModuleUsingItem | null)[];
}

export interface Module {
    $ast: "Module";
    moduleType: ModuleType;
    name: string;
    paths: (ModuleUsingPath | null)[];
    declarations: (Declaration | null)[];
}

