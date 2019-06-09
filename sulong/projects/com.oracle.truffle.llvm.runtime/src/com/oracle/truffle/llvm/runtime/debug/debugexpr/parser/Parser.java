package com.oracle.truffle.llvm.runtime.debug.debugexpr.parser;

import java.util.LinkedList;
import com.oracle.truffle.llvm.runtime.nodes.api.LLVMExpressionNode;
import com.oracle.truffle.llvm.runtime.ArithmeticOperation;
import com.oracle.truffle.llvm.runtime.debug.debugexpr.nodes.*;
import com.oracle.truffle.llvm.runtime.debug.debugexpr.nodes.DebugExprCompareNode.Op;
// Set the name of your grammar here (and at the end of this grammar):

import java.util.List;

public class Parser {
	public static final int _EOF = 0;
	public static final int _ident = 1;
	public static final int _number = 2;
	public static final int _floatnumber = 3;
	public static final int _charConst = 4;
	public static final int _stringType = 5;
	public static final int _lpar = 6;
	public static final int _asterisc = 7;
	public static final int _signed = 8;
	public static final int _unsigned = 9;
	public static final int _int = 10;
	public static final int _long = 11;
	public static final int _short = 12;
	public static final int _float = 13;
	public static final int _double = 14;
	public static final int _char = 15;
	public static final int maxT = 45;

	static final boolean T = true;
	static final boolean x = false;
	static final int minErrDist = 2;

	public Token t;    // last recognized token
	public Token la;   // lookahead token
	int errDist = minErrDist;
	
	public Scanner scanner;
	public Errors errors;

	//only for the editor
	private boolean isContentAssistant = false;
	private boolean errorsDetected = false;
	private boolean updateProposals = false;

	private int stopPosition = 0;
	private int proposalToken = _EOF;
	private List<String> ccSymbols = null;
	private List<String> proposals = null;
	private Token dummy = new Token();


	boolean IsCast() {
	Token peek = scanner.Peek();
	if(la.kind==_lpar) {
	    while(peek.kind==_asterisc) peek=scanner.Peek();
	    int k = peek.kind;
	    if(k==_signed||k==_unsigned||k==_int||k==_long||k==_char||k==_short||k==_float||k==_double) return true;
	}
	return false;
}

private LLVMExpressionNode astRoot=null;
private DebugExprNodeFactory NF=null;
public final static DebugExprErrorNode noObjNode = DebugExprErrorNode.create("<cannot find expression>");
public final static DebugExprErrorNode errorObjNode = DebugExprErrorNode.create("<cannot evaluate expression>");

public void setNodeFactory(DebugExprNodeFactory nodeFactory) {
	if(NF==null) NF=nodeFactory;
}

public int GetErrors() {
	return errors.count;
}

public LLVMExpressionNode GetASTRoot() {return astRoot; }
// If you want your generated compiler case insensitive add the
// keyword IGNORECASE here.




	public Parser(Scanner scanner) {
		this.scanner = scanner;
		errors = new Errors();
	}

	void SynErr (int n) {
		if (errDist >= minErrDist) errors.SynErr(la.line, la.col, n);
		errDist = 0;
		
		//for the editor
		errorsDetected = true;
	}

	public void SemErr (String msg) {
		if (errDist >= minErrDist) errors.SemErr(t.line, t.col, msg);
		errDist = 0;

		//for the editor
		errorsDetected = true;
	}
	 
	void Get () {
		if(isContentAssistant && updateProposals){
			la = la.next;
			if(!errorsDetected){
				proposals = ccSymbols;
			
				errorsDetected = true;
			}
		}
		
		else{
			for (;;) {
				t = la;
				la = scanner.Scan();
				if (la.kind <= maxT) {
					++errDist;
					break;
				} 

				la = t;

			}
		}
				

		

		//auch aktuellen token mitgeben,
		//if la.charPos >= current Token && la.charPos < stopPosition + la.val.length()
		//  Token temp = la.clone();
		//	la.kind = proposalToken;


		//only for the Editor
		if(isContentAssistant && !errorsDetected && la.charPos >= stopPosition + la.val.length()){
			dummy = createDummy();
			dummy.next = la;
			la = dummy;
			updateProposals = true;
			
		}
		ccSymbols = null;
	}
	
	void Expect (int n) {
		if (la.kind==n) Get(); else { SynErr(n); }
	}
	
	boolean StartOf (int s) {
		return set[s][la.kind];
	}
	
	void ExpectWeak (int n, int follow) {
		if (la.kind == n) Get();
		else {
			SynErr(n);
			while (!StartOf(follow)) Get();
		}
	}
	
	boolean WeakSeparator (int n, int syFol, int repFol) {
		int kind = la.kind;
		if (kind == n) { Get(); return true; }
		else if (StartOf(repFol)) return false;
		else {
			SynErr(n);
			while (!(set[syFol][kind] || set[repFol][kind] || set[0][kind])) {
				Get();
				kind = la.kind;
			}
			return StartOf(syFol);
		}
	}
	
	void DebugExpr() {
		LLVMExpressionNode n=null; 
		n = Expr();
		if(errors.count==0) astRoot =n; 
	}

	LLVMExpressionNode  Expr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode nThen=null, nElse=null; 
		n = LogOrExpr();
		if (la.kind == 42) {
			Get();
			nThen = Expr();
			Expect(43);
			nElse = Expr();
			n = NF.createTernaryNode(n, nThen, nElse);
		}
		return n;
	}

	LLVMExpressionNode  PrimExpr() {
		LLVMExpressionNode  n;
		n=errorObjNode; 
		switch (la.kind) {
		case 1: {
			Get();
			n = NF.createVarNode(t.val);
			break;
		}
		case 2: {
			Get();
			n = NF.createIntegerConstant(Integer.parseInt(t.val)); 
			break;
		}
		case 3: {
			Get();
			n = NF.createFloatConstant(Float.parseFloat(t.val)); 
			break;
		}
		case 4: {
			Get();
			break;
		}
		case 5: {
			Get();
			break;
		}
		case 6: {
			Get();
			n = Expr();
			Expect(16);
			break;
		}
		default: SynErr(46); break;
		}
		return n;
	}

	LLVMExpressionNode  Designator() {
		LLVMExpressionNode  n;
		LLVMExpressionNode idx=null; List<LLVMExpressionNode> l; 
		n = PrimExpr();
		while (StartOf(1)) {
			if (la.kind == 17) {
				Get();
				idx = Expr();
				Expect(18);
			} else if (la.kind == 6) {
				l = ActPars();
			} else if (la.kind == 19) {
				Get();
				Expect(1);
			} else {
				Get();
				Expect(1);
			}
		}
		return n;
	}

	List  ActPars() {
		List  l;
		LLVMExpressionNode n1=null, n2=null; l = new LinkedList<LLVMExpressionNode>(); 
		Expect(6);
		if (StartOf(2)) {
			n1 = Expr();
			l.add(n1); 
			while (la.kind == 21) {
				Get();
				n2 = Expr();
				l.add(n2); 
			}
		}
		Expect(16);
		return l;
	}

	LLVMExpressionNode  UnaryExpr() {
		LLVMExpressionNode  n;
		n=null; char kind='\0'; DebugExprType typeP=null;
		if (StartOf(3)) {
			n = Designator();
		} else if (StartOf(4)) {
			kind = UnaryOp();
			n = CastExpr();
			n = NF.createUnaryOpNode(n, kind); 
		} else if (la.kind == 22) {
			Get();
			Expect(6);
			typeP = DType();
			Expect(16);
			n=NF.createSizeofNode(typeP); 
		} else SynErr(47);
		return n;
	}

	char  UnaryOp() {
		char  kind;
		kind='\0'; 
		switch (la.kind) {
		case 23: {
			Get();
			break;
		}
		case 7: {
			Get();
			break;
		}
		case 24: {
			Get();
			break;
		}
		case 25: {
			Get();
			break;
		}
		case 26: {
			Get();
			break;
		}
		case 27: {
			Get();
			break;
		}
		default: SynErr(48); break;
		}
		kind = t.val.charAt(0); 
		return kind;
	}

	LLVMExpressionNode  CastExpr() {
		LLVMExpressionNode  n;
		DebugExprType typeP=null; 
		if (IsCast()) {
			Expect(6);
			typeP = DType();
			Expect(16);
		}
		n = UnaryExpr();
		if(typeP!=null) { n = NF.createCast(n, typeP); } 
		return n;
	}

	DebugExprType  DType() {
		DebugExprType  ty;
		ty = BaseType();
		if (la.kind == 7 || la.kind == 16 || la.kind == 17) {
			while (la.kind == 7) {
				Get();
				SemErr("Pointer types are not available yet"); 
			}
		} else if (la.kind == 23) {
			Get();
			SemErr("Reference types are not available yet"); 
		} else SynErr(49);
		while (la.kind == 17) {
			Get();
			SemErr("Array types are not available yet"); 
			if (la.kind == 2) {
				Get();
			}
			Expect(18);
		}
		return ty;
	}

	LLVMExpressionNode  MultExpr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode n1=null; 
		n = CastExpr();
		while (la.kind == 7 || la.kind == 28 || la.kind == 29) {
			if (la.kind == 7) {
				Get();
				n1 = CastExpr();
				n = NF.createArithmeticOp(ArithmeticOperation.MUL, null, n, n1); 
			} else if (la.kind == 28) {
				Get();
				n1 = CastExpr();
				n = NF.createArithmeticOp(ArithmeticOperation.DIV, null, n, n1); 
			} else {
				Get();
				n1 = CastExpr();
				n = NF.createArithmeticOp(ArithmeticOperation.REM, null, n, n1); 
			}
		}
		return n;
	}

	LLVMExpressionNode  AddExpr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode n1=null; 
		n = MultExpr();
		while (la.kind == 24 || la.kind == 25) {
			if (la.kind == 24) {
				Get();
				n1 = MultExpr();
				n = NF.createAddNode(n, n1); 
			} else {
				Get();
				n1 = MultExpr();
				n = NF.createSubNode(n, n1); 
			}
		}
		return n;
	}

	LLVMExpressionNode  ShiftExpr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode n1=null; 
		n = AddExpr();
		while (la.kind == 30 || la.kind == 31) {
			if (la.kind == 30) {
				Get();
				n1 = AddExpr();
				n = NF.createArithmeticOp(ArithmeticOperation.SHL, null, n, n1); 
			} else {
				Get();
				n1 = AddExpr();
				n = NF.createArithmeticOp(ArithmeticOperation.ASHR, null, n, n1); 
			}
		}
		return n;
	}

	LLVMExpressionNode  RelExpr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode n1=null; 
		n = ShiftExpr();
		while (StartOf(5)) {
			if (la.kind == 32) {
				Get();
				n1 = ShiftExpr();
				n = NF.createCompareNode(n, Op.LT, n1); 
			} else if (la.kind == 33) {
				Get();
				n1 = ShiftExpr();
				n = NF.createCompareNode(n, Op.GT, n1); 
			} else if (la.kind == 34) {
				Get();
				n1 = ShiftExpr();
				n = NF.createCompareNode(n, Op.LE, n1); 
			} else {
				Get();
				n1 = ShiftExpr();
				n = NF.createCompareNode(n, Op.GE, n1); 
			}
		}
		return n;
	}

	LLVMExpressionNode  EqExpr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode n1=null; 
		n = RelExpr();
		while (la.kind == 36 || la.kind == 37) {
			if (la.kind == 36) {
				Get();
				n1 = RelExpr();
				n = NF.createCompareNode(n, Op.EQ, n1); 
			} else {
				Get();
				n1 = RelExpr();
				n = NF.createCompareNode(n, Op.NE, n1); 
			}
		}
		return n;
	}

	LLVMExpressionNode  AndExpr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode n1=null; 
		n = EqExpr();
		while (la.kind == 23) {
			Get();
			n1 = EqExpr();
			n = NF.createArithmeticOp(ArithmeticOperation.AND, null, n, n1); 
		}
		return n;
	}

	LLVMExpressionNode  XorExpr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode n1=null; 
		n = AndExpr();
		while (la.kind == 38) {
			Get();
			n1 = AndExpr();
			n = NF.createArithmeticOp(ArithmeticOperation.XOR, null, n, n1); 
		}
		return n;
	}

	LLVMExpressionNode  OrExpr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode n1=null; 
		n = XorExpr();
		while (la.kind == 39) {
			Get();
			n1 = XorExpr();
			n = NF.createArithmeticOp(ArithmeticOperation.OR, null, n, n1); 
		}
		return n;
	}

	LLVMExpressionNode  LogAndExpr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode n1=null; 
		n = OrExpr();
		while (la.kind == 40) {
			Get();
			n1 = OrExpr();
			n= NF.createLogicalAndNode(n, n1); 
		}
		return n;
	}

	LLVMExpressionNode  LogOrExpr() {
		LLVMExpressionNode  n;
		LLVMExpressionNode n1=null; 
		n = LogAndExpr();
		while (la.kind == 41) {
			Get();
			n1 = LogAndExpr();
			n= NF.createLogicalOrNode(n, n1); 
		}
		return n;
	}

	DebugExprType  BaseType() {
		DebugExprType  ty;
		ty=null; boolean signed=false;
		switch (la.kind) {
		case 44: {
			Get();
			ty = DebugExprType.getVoidType(); 
			break;
		}
		case 1: {
			Get();
			break;
		}
		case 8: case 9: {
			if (la.kind == 8) {
				Get();
				signed = true; 
			} else {
				Get();
				signed = false; 
			}
			if (StartOf(6)) {
				if (la.kind == 15) {
					Get();
					ty = DebugExprType.getIntType(8, signed); 
				} else if (la.kind == 12) {
					Get();
					ty = DebugExprType.getIntType(16, signed); 
				} else if (la.kind == 10) {
					Get();
					ty = DebugExprType.getIntType(32, signed); 
				} else {
					Get();
					ty = DebugExprType.getIntType(64, signed); 
				}
			}
			break;
		}
		case 15: {
			Get();
			ty = DebugExprType.getIntType(8, false);
			break;
		}
		case 12: {
			Get();
			ty = DebugExprType.getIntType(16, true);
			break;
		}
		case 10: {
			Get();
			ty = DebugExprType.getIntType(32, true);
			break;
		}
		case 11: {
			Get();
			ty = DebugExprType.getIntType(64, true);
			if (la.kind == 14) {
				Get();
				ty = DebugExprType.getFloatType(128); 
			}
			break;
		}
		case 13: {
			Get();
			ty = DebugExprType.getFloatType(32);
			break;
		}
		case 14: {
			Get();
			ty = DebugExprType.getFloatType(64);
			break;
		}
		default: SynErr(50); break;
		}
		return ty;
	}



	public void Parse() {
		la = new Token();
		la.val = "";		
		Get();
		DebugExpr();
		Expect(0);

	}

	private static final boolean[][] set = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,T,x, x,x,x,x, x,x,x,x, x,T,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,T,T, T,T,T,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,T,T, T,T,T,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,T,T, T,T,T,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,T,T,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,T,T,T, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,T,T, T,x,x,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x}

	};
 
	
	//only for the editor
	public Parser(Scanner scanner, int proposalToken, int stopPosition){
		this(scanner);
		isContentAssistant = true;
		this.proposalToken = proposalToken;
		this.stopPosition = stopPosition;
	}

	public String ParseErrors(){
		java.io.PrintStream oldStream = System.out;
		
		java.io.OutputStream out = new java.io.ByteArrayOutputStream();
		java.io.PrintStream newStream = new java.io.PrintStream(out);
		
		errors.errorStream = newStream;
				
		Parse();

		String errorStream = out.toString();
		errors.errorStream = oldStream;

		return errorStream;

	}

	public List<String> getCodeCompletionProposals(){
		return proposals;
	}

	private Token createDummy(){
		Token token = new Token();
		
		token.pos = la.pos;
		token.charPos = la.charPos;
		token.line = la.line;
		token.col = la.col;
		
		token.kind = proposalToken;
		token.val = "";
		
		
		return token;
	}
} // end Parser


class Errors {
	public int count = 0;                                    // number of errors detected
	public java.io.PrintStream errorStream = System.out;     // error messages go to this stream
	public String errMsgFormat = "-- line {0} col {1}: {2}"; // 0=line, 1=column, 2=text
	
	protected void printMsg(int line, int column, String msg) {
		StringBuffer b = new StringBuffer(errMsgFormat);
		int pos = b.indexOf("{0}");
		if (pos >= 0) { b.delete(pos, pos+3); b.insert(pos, line); }
		pos = b.indexOf("{1}");
		if (pos >= 0) { b.delete(pos, pos+3); b.insert(pos, column); }
		pos = b.indexOf("{2}");
		if (pos >= 0) b.replace(pos, pos+3, msg);
		errorStream.println(b.toString());
	}
	
	public void SynErr (int line, int col, int n) {
		String s;
		switch (n) {
			case 0: s = "EOF expected"; break;
			case 1: s = "ident expected"; break;
			case 2: s = "number expected"; break;
			case 3: s = "floatnumber expected"; break;
			case 4: s = "charConst expected"; break;
			case 5: s = "stringType expected"; break;
			case 6: s = "lpar expected"; break;
			case 7: s = "asterisc expected"; break;
			case 8: s = "signed expected"; break;
			case 9: s = "unsigned expected"; break;
			case 10: s = "int expected"; break;
			case 11: s = "long expected"; break;
			case 12: s = "short expected"; break;
			case 13: s = "float expected"; break;
			case 14: s = "double expected"; break;
			case 15: s = "char expected"; break;
			case 16: s = "\")\" expected"; break;
			case 17: s = "\"[\" expected"; break;
			case 18: s = "\"]\" expected"; break;
			case 19: s = "\".\" expected"; break;
			case 20: s = "\"->\" expected"; break;
			case 21: s = "\",\" expected"; break;
			case 22: s = "\"sizeof\" expected"; break;
			case 23: s = "\"&\" expected"; break;
			case 24: s = "\"+\" expected"; break;
			case 25: s = "\"-\" expected"; break;
			case 26: s = "\"~\" expected"; break;
			case 27: s = "\"!\" expected"; break;
			case 28: s = "\"/\" expected"; break;
			case 29: s = "\"%\" expected"; break;
			case 30: s = "\"<<\" expected"; break;
			case 31: s = "\">>\" expected"; break;
			case 32: s = "\"<\" expected"; break;
			case 33: s = "\">\" expected"; break;
			case 34: s = "\"<=\" expected"; break;
			case 35: s = "\">=\" expected"; break;
			case 36: s = "\"==\" expected"; break;
			case 37: s = "\"!=\" expected"; break;
			case 38: s = "\"^\" expected"; break;
			case 39: s = "\"|\" expected"; break;
			case 40: s = "\"&&\" expected"; break;
			case 41: s = "\"||\" expected"; break;
			case 42: s = "\"?\" expected"; break;
			case 43: s = "\":\" expected"; break;
			case 44: s = "\"void\" expected"; break;
			case 45: s = "??? expected"; break;
			case 46: s = "invalid PrimExpr"; break;
			case 47: s = "invalid UnaryExpr"; break;
			case 48: s = "invalid UnaryOp"; break;
			case 49: s = "invalid DType"; break;
			case 50: s = "invalid BaseType"; break;
			default: s = "error " + n; break;
		}
		printMsg(line, col, s);
		count++;
	}

	public void SemErr (int line, int col, String s) {	
		printMsg(line, col, s);
		count++;
	}
	
	public void SemErr (String s) {
		errorStream.println(s);
		count++;
	}
	
	public void Warning (int line, int col, String s) {	
		printMsg(line, col, s);
	}
	
	public void Warning (String s) {
		errorStream.println(s);
	}
} // Errors


class FatalError extends RuntimeException {
	public static final long serialVersionUID = 1L;
	public FatalError(String s) { super(s); }
}
