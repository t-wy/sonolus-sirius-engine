#ifndef MaxForSize
const int MaxForSize = 16;
#endif

using namespace std;
#include<jsoncpp/json/json.h>
#include<openssl/ssl.h>

#include"modules/modules.h"

#include"items/Exception.h"
#include"items/EngineEnums.h"
#include"items/FuncNode.h"
#include"items/EngineConfiguration.h"
#include"items/EngineData.h"
#include"items/EngineTutorialData.h"
#include"items/EnginePreviewData.h"

#include"functions/functions.h"
#ifndef DISABLE_REDEFINE
#include"functions/redefine.h"
#endif
#ifndef DISABLE_JSPREFER
typedef FuncNode var;
typedef FuncNode let;
#endif

EngineData engineData;
EngineTutorialData engineTutorialData;
EngineConfiguration engineConfiguration;
EnginePreviewData enginePreviewData;
FuncNode tutorialPreprocess = 0;
FuncNode tutorialNavigate = 0;
FuncNode tutorialUpdate = 0;

#include"blocks/Archetype.h"
#include"blocks/Define.h"
#include"blocks/Pointer.h"

map<EngineDataNode, int> hashMap;
// 双哈希 + 手动哈希表 O(n)
// const int64_t k1 = 23;
// const int64_t k2 = 55331;
// const int64_t p1 = 1e9 + 7;
// const int64_t p2 = 998244353;
// struct hashMap {
//     int *map1, *map2;
//     hashMap() {
//         map1 = new int[1 << 20];
//         map2 = new int[1 << 20];
//         memset(map1, -1, sizeof(map1));
//         memset(map2, -1, sizeof(map2));
//     }
//     int64_t getHash(EngineDataNode v, bool hashType) {
//         string tmp = v.type;
//         if (v.type == "value") tmp += to_string(v.value.value);
//         else {
//             tmp += v.func.func;
//             for (int i = 0; i < v.func.args.size(); i++) tmp += to_string(v.func.args[i]);
//         } int64_t hash = 0;
//         for (int i = 0; i < tmp.size(); i++) 
//             hash *= hashType ? k1 : k2, hash %= hashType ? p1 : p2,
//             hash += tmp[i], hash %= hashType ? p1 : p2;
//         return hash;
//     }
//     void insert(EngineDataNode key, int value) {
//         int64_t hash1 = getHash(key, 0);
//         int64_t hash2 = getHash(key, 1);
//         hash1 %= (1 << 20); hash2 %= (1 << 20);
//         map1[hash1] = value; map2[hash2] = value;
//     }
//     int get(EngineDataNode key) {
//         int64_t hash1 = getHash(key, 0);
//         int64_t hash2 = getHash(key, 1);
//         hash1 %= (1 << 20); hash2 %= (1 << 20);
//         if (map1[hash1] != map2[hash2]) throw runtime_error("Hash Collision!");
//         return map1[hash1];
//     }
//     bool exist(EngineDataNode key) {
//         int64_t hash1 = getHash(key, 0);
//         int64_t hash2 = getHash(key, 1);
//         hash1 %= (1 << 20); hash2 %= (1 << 20);
//         if (map1[hash1] != map2[hash2]) throw runtime_error("Hash Collision!");
//         return map1[hash1] != -1;
//     }
// }hashMap;

int globalCounter = 0;
int lastGlobalCounter = 0;

template<typename T>
int buildScript(FuncNode script, T& nodesContainer, int blockCounter = 0) {
	globalCounter++;
//	if (hashMap.find(script.stringify(0, 1)) != hashMap.end()) return hashMap[script.stringify(0, 5)];
    EngineDataNode res;
    if (script.isValue == true) res = EngineDataValueNode(script.value);
    else {
        // Return 函数判断
/*        if (script.func == "Return") {
            script.func = "Break"; FuncNode code = script.args[0];
            script.args = {blockCounter, code};
        }*/
        // 其余函数
        vector<double> args;
        for (int i = 0; i < script.args.size(); i++) 
            args.push_back(buildScript(
                script.args[i],
                nodesContainer,
                blockCounter + (script.func == "Block")));
        res = EngineDataFunctionNode(script.func, args);
    } 
    // if (hashMap.exist(res)) return hashMap.get(res);
    // hashMap.insert(res, nodesContainer.nodes.size()); nodesContainer.nodes.push_back(res);
    // return hashMap.get(res);
    if (hashMap.find(res) != hashMap.end()) return hashMap[res];
    hashMap[res] = nodesContainer.nodes.size(); nodesContainer.nodes.push_back(res);
    return hashMap[res];
/*	hashMap[script.stringify(0, 1)] = nodesContainer.nodes.size(); nodesContainer.nodes.push_back(res);
	return hashMap[script.stringify(0, 1)];*/
}

int buildFuncNode(FuncNode func) {
    return buildScript(func, engineData);
}

int buildFuncNode2(FuncNode func) {
    return buildScript(func, engineTutorialData);
}

int buildFuncNode3(FuncNode func) {
    return buildScript(func, enginePreviewData);
}

time_t millitime() {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

template<typename T>
void buildArchetype(T archetype) {
	lastGlobalCounter = globalCounter;
    #ifdef play
    time_t st = millitime();
    EngineDataArchetype newArchetype;
    cout << "Solving Archetype \"" << archetype.name << "\"..." << endl;
    newArchetype.name = archetype.name;
    newArchetype.hasInput = archetype.hasInput;
    newArchetype.preprocess.order = archetype.preprocessOrder;
    newArchetype.preprocess.index = buildFuncNode(Block(archetype.preprocess()));
    newArchetype.spawnOrder.order = archetype.spawnOrderOrder;
    newArchetype.spawnOrder.index = buildFuncNode(Block(archetype.spawnOrder()));
    newArchetype.shouldSpawn.order = archetype.shouldSpawnOrder;
    newArchetype.shouldSpawn.index = buildFuncNode(Block(archetype.shouldSpawn()));
    newArchetype.initialize.order = archetype.initializeOrder;
    newArchetype.initialize.index = buildFuncNode(Block(archetype.initialize()));
    newArchetype.updateSequential.order = archetype.updateSequentialOrder;
    newArchetype.updateSequential.index = buildFuncNode(Block(archetype.updateSequential()));
//	archetype.updateSequential();
    newArchetype.touch.order = archetype.touchOrder;
    newArchetype.touch.index = buildFuncNode(Block(archetype.touch()));
    newArchetype.updateParallel.order = archetype.updateParallelOrder;
    newArchetype.updateParallel.index = buildFuncNode(Block(archetype.updateParallel()));
    newArchetype.terminate.order = archetype.terminateOrder;
    newArchetype.terminate.index = buildFuncNode(Block(archetype.terminate()));
    newArchetype.data = archetype.data;
    engineData.archetypes.push_back(newArchetype);
    time_t d = millitime() - st;
    cout << "Solved Archetype \"" << archetype.name << "\" in " << d << "ms. Speed: " 
		 << fixed << setprecision(0) 
         << 1.0 * (globalCounter - lastGlobalCounter) / (1.0 * d / 1000) << " nodes/s. Total: " 
		 << (globalCounter - lastGlobalCounter) << " nodes." << endl;
    #elif preview
    time_t st = millitime();
    EnginePreviewDataArchetype newArchetype;
    cout << "Solving Archetype \"" << archetype.name << "\"..." << endl;
    newArchetype.name = archetype.name;
    newArchetype.preprocess.order = archetype.preprocessOrder;
    newArchetype.preprocess.index = buildFuncNode3(archetype.preprocess());
    newArchetype.render.order = archetype.renderOrder;
    newArchetype.render.index = buildFuncNode3(archetype.render());
    newArchetype.data = archetype.data;
    enginePreviewData.archetypes.push_back(newArchetype);
    time_t d = millitime() - st;
    cout << "Solved Archetype \"" << archetype.name << "\" in " << d << "ms. Speed: " 
		 << fixed << setprecision(0)
         << 1.0 * (globalCounter - lastGlobalCounter) / (1.0 * d / 1000) << " nodes/s. Total: " 
		 << (globalCounter - lastGlobalCounter) << " nodes." << endl;
    #endif
}

template<typename T, typename... Args> 
void buildArchetype(T unused, Args... args) {
    buildArchetype<T>(unused); buildArchetype<Args...>(args...);
}

template<typename... Args>
void build(buffer& configurationBuffer, buffer& dataBuffer) {
    Json::Value configuration = engineConfiguration.toJsonObject();
    configurationBuffer = compress_gzip(json_encode(configuration));
#ifdef play
    buildArchetype<Args...>(Args()...);
    dataBuffer = compress_gzip(json_encode(engineData.toJsonObject()));
#elif tutorial
    engineTutorialData.preprocess = buildFuncNode2(tutorialPreprocess);
    engineTutorialData.navigate = buildFuncNode2(tutorialNavigate);
    engineTutorialData.update = buildFuncNode2(tutorialUpdate);
    dataBuffer = compress_gzip(json_encode(engineTutorialData.toJsonObject()));
#elif preview
    buildArchetype<Args...>(Args()...);
    dataBuffer = compress_gzip(json_encode(enginePreviewData.toJsonObject()));
#endif
}

int ForPtIterator = 0;
#define IF(cond) If(cond, Execute(
#define ELSE ), Execute(
#define FI ))
#define FOR(i, st, en, step) [&](){\
	FuncNode i = ForPt[++ForPtIterator].get(); \
	blockCounter += 2; \
    auto res = __builtin_Block(Execute({\
        ForPt[ForPtIterator].set(st - step), \
        While(ForPt[ForPtIterator].get() < en - step, __builtin_Block(Execute({\
            ForPt[ForPtIterator].set(ForPt[ForPtIterator].get() + step), \
            Execute(
#define DONE )}))) \
    })); \
	blockCounter -= 2; ForPtIterator--; \
	return res; \
}()
#define CONTINUE Break(1, 0)
#define BREAK Break(2, 0)

#include"items/PlayData.h"
#include"items/TutorialData.h"
#include"items/PreviewData.h"
