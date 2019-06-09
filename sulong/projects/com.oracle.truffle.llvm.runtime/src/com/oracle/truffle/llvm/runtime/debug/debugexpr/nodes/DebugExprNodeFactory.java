package com.oracle.truffle.llvm.runtime.debug.debugexpr.nodes;

import com.oracle.truffle.api.Scope;
import com.oracle.truffle.api.TruffleLanguage.ContextReference;
import com.oracle.truffle.llvm.runtime.ArithmeticOperation;
import com.oracle.truffle.llvm.runtime.LLVMContext;
import com.oracle.truffle.llvm.runtime.debug.debugexpr.nodes.DebugExprBitFlipNodeFactory.BitFlipNodeGen;
import com.oracle.truffle.llvm.runtime.debug.debugexpr.nodes.DebugExprCompareNode.Op;
import com.oracle.truffle.llvm.runtime.debug.debugexpr.nodes.DebugExprNotNodeFactory.NotNodeGen;
import com.oracle.truffle.llvm.runtime.debug.debugexpr.nodes.DebugExprShortCircuitEvaluationNodeFactory.DebugExprLogicalAndNodeGen;
import com.oracle.truffle.llvm.runtime.debug.debugexpr.nodes.DebugExprShortCircuitEvaluationNodeFactory.DebugExprLogicalOrNodeGen;
import com.oracle.truffle.llvm.runtime.debug.debugexpr.parser.DebugExprType;
import com.oracle.truffle.llvm.runtime.nodes.api.LLVMExpressionNode;
import com.oracle.truffle.llvm.runtime.types.PrimitiveType;
import com.oracle.truffle.llvm.runtime.types.Type;

public final class DebugExprNodeFactory {
    private ContextReference<LLVMContext> contextReference;
    public final static DebugExprErrorNode noObjNode = DebugExprErrorNode.create("<cannot find expression>");
    public final static DebugExprErrorNode errorObjNode = DebugExprErrorNode.create("<cannot evaluate expression>");
    private Iterable<Scope> scopes;

    private DebugExprNodeFactory(ContextReference<LLVMContext> contextReference, Iterable<Scope> scopes) {
        this.contextReference = contextReference;
        this.scopes = scopes;
    }

    private static DebugExprNodeFactory INSTANCE = null;

    public static DebugExprNodeFactory getInstance(ContextReference<LLVMContext> contextReference, Iterable<Scope> scopes) {
        if (INSTANCE == null || contextReference != INSTANCE.contextReference) {
            INSTANCE = new DebugExprNodeFactory(contextReference, scopes);
        }
        return INSTANCE;
    }

    public LLVMExpressionNode createArithmeticOp(ArithmeticOperation op, Type type, LLVMExpressionNode left, LLVMExpressionNode right) {
        return contextReference.get().getNodeFactory().createArithmeticOp(op, type, left, right);
    }

    public LLVMExpressionNode createAddNode(LLVMExpressionNode left, LLVMExpressionNode right) {
        return contextReference.get().getNodeFactory().createArithmeticOp(ArithmeticOperation.ADD, null, left, right);
    }

    public LLVMExpressionNode createSubNode(LLVMExpressionNode left, LLVMExpressionNode right) {
        return contextReference.get().getNodeFactory().createArithmeticOp(ArithmeticOperation.SUB, null, left, right);
    }

    public LLVMExpressionNode createMulNode(LLVMExpressionNode left, LLVMExpressionNode right) {
        return contextReference.get().getNodeFactory().createArithmeticOp(ArithmeticOperation.MUL, null, left, right);
    }

    @SuppressWarnings("static-method")
    public LLVMExpressionNode createTernaryNode(LLVMExpressionNode condition, LLVMExpressionNode thenNode, LLVMExpressionNode elseNode) {
        return new DebugExprTernaryNode(condition, thenNode, elseNode);
    }

    public LLVMExpressionNode createUnaryOpNode(LLVMExpressionNode node, char unaryOp) {
        switch (unaryOp) {
            case '&':
            case '*':
                return errorObjNode;
            case '+':
                return node;
            case '-':
                return createSubNode(createIntegerConstant(0), node);
            case '~':
                return BitFlipNodeGen.create(node);
            case '!':
                return NotNodeGen.create(node);
            default:
                return errorObjNode;
        }
    }

    @SuppressWarnings("static-method")
    public LLVMExpressionNode createVarNode(String name) {
        return new DebugExprVarNode(name, scopes);
    }

    @SuppressWarnings("static-method")
    public LLVMExpressionNode createSizeofNode(DebugExprType type) {
        return new DebugExprSizeofNode(type);
    }

    @SuppressWarnings("static-method")
    public LLVMExpressionNode createLogicalAndNode(LLVMExpressionNode left, LLVMExpressionNode right) {
        return DebugExprLogicalAndNodeGen.create(left, right);
    }

    @SuppressWarnings("static-method")
    public LLVMExpressionNode createLogicalOrNode(LLVMExpressionNode left, LLVMExpressionNode right) {
        return DebugExprLogicalOrNodeGen.create(left, right);
    }

    @SuppressWarnings("static-method")
    public LLVMExpressionNode createErrorNode(Object errorObj) {
        return DebugExprErrorNode.create(errorObj);
    }

    public LLVMExpressionNode createCompareNode(LLVMExpressionNode left, Op op, LLVMExpressionNode right) {
        return new DebugExprCompareNode(contextReference.get().getNodeFactory(), left, op, right);
    }

    public LLVMExpressionNode createIntegerConstant(int value) {
        return contextReference.get().getNodeFactory().createSimpleConstantNoArray(value, PrimitiveType.I32);
    }

    public LLVMExpressionNode createFloatConstant(float value) {
        return contextReference.get().getNodeFactory().createSimpleConstantNoArray(value, PrimitiveType.FLOAT);
    }

    public LLVMExpressionNode createCast(LLVMExpressionNode node, DebugExprType type) {
        if (type.isUnsigned())
            return contextReference.get().getNodeFactory().createUnsignedCast(node, type.getLLVMRuntimeType());
        else
            return contextReference.get().getNodeFactory().createSignedCast(node, type.getLLVMRuntimeType());
    }

}
