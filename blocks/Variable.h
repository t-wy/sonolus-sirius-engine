stack<vector<FuncNode> > nodesContainer;
stack<int> blockCounter;
stack<bool> addBlockCounter;
void createNodeContainer(bool);
void R(FuncNode);

template<int identifierId>
class Variable {
    public:

    int offset;
    Variable(){
    	offset = allocatorSize[identifierId]++;
    }
    Variable(int val) {
    	offset = allocatorSize[identifierId]++;
		R(FuncNode(RuntimeFunction.Set, {identifierId, offset, val}));
    }
    Variable(double val) {
    	offset = allocatorSize[identifierId]++;
		R(FuncNode(RuntimeFunction.Set, {identifierId, offset, val}));
    }
    template<int T> Variable(Variable<T> val) {
    	offset = allocatorSize[identifierId]++;
		R(FuncNode(RuntimeFunction.Set, {identifierId, offset, val.get()}));
    }
    Variable(FuncNode val) {
    	offset = allocatorSize[identifierId]++;
		R(FuncNode(RuntimeFunction.Set, {identifierId, offset, val}));
    }
    Variable(int offset, bool unused) {
    	offset = offset;
    }

	FuncNode get() {
		return FuncNode(RuntimeFunction.Get, {identifierId, offset});
	}
    void set(int val) {
		R(FuncNode(RuntimeFunction.Set, {identifierId, offset, val}));
    }
    void set(double val) {
		R(FuncNode(RuntimeFunction.Set, {identifierId, offset, val}));
    }
    void set(FuncNode val) {
		R(FuncNode(RuntimeFunction.Set, {identifierId, offset, val}));
    }
    template<int T> void set(Variable<T> val) {
		R(FuncNode(RuntimeFunction.Set, {identifierId, offset, val.get()}));
    }

	template<typename T>
    Variable operator = (T val) { set(val); return (*this); };

    operator FuncNode() {
    	return get();
    }

    int classSize = 1;
   	vector<function<void(FuncNode)> > deserializiers = {
   		[&](FuncNode var){ set(var); }
   	};
   	vector<function<FuncNode()> > serializiers = {
   		[&](){ return get(); }
   	};
   	vector<FuncNode> serialize() {
   		return { get() };
   	}
   	void deserialize(vector<FuncNode> val) {
   		assert(val.size() == classSize);
   		set(val[0]);
   	}
};

void createNodeContainer(bool add = true) {
	nodesContainer.push(vector<FuncNode>());
	if (add) blockCounter.push(1);
	else blockCounter.top() += 1;
	addBlockCounter.push(add);
}
void R(FuncNode body) {
	if (nodesContainer.size() == 0) throwError("You shouldn't execute anything outside Archetypes!");
	nodesContainer.top().push_back(body);
}
FuncNode mergeNodeContainer() {
	assert(nodesContainer.size());
	auto c = nodesContainer.top(); nodesContainer.pop();
	if (addBlockCounter.top()) blockCounter.pop();
	else blockCounter.top() -= 1;
	addBlockCounter.pop();
	FuncNode res = FuncNode(RuntimeFunction.Block, {
		c.size() == 1 ? c[0] : FuncNode(RuntimeFunction.Execute, c)
	}); return res;
}
