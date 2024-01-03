class SiriusSound: public Archetype {
	public:

	static constexpr const char* name = "Sirius Sound";
	bool hasInput = true;
	
	defineEntityData(beat);
	defineEntityData(lane);
	defineEntityData(laneLength);
	defineEntityData(holdType);
    Variable<EntityMemoryId> enLane;
    Variable<EntityMemoryId> inputTimeMin;
    Variable<EntityMemoryId> inputTimeMax;
	Variable<EntityMemoryId> isHolding;
	Variable<EntityMemoryId> lastHoldTime;

    SonolusApi preprocess() {
   		FUNCBEGIN
        IF (LevelOption.get(Options.Mirror)) lane.set(13 - enLane); FI
		enLane = lane + laneLength - 1;
		inputTimeMin = beat - judgment.bad;
		inputTimeMax = beat + judgment.bad;
		isHolding = false;
		lastHoldTime = -1;
        return VOID;
    }
    
    SonolusApi spawnOrder() { return 1000 + beat; }
    SonolusApi shouldSpawn() { return times.now > beat - appearTime; }

	SonolusApi complete(let t = times.now) {
		FUNCBEGIN
		var res = 0, res2 = 0;
		IF (Abs(t - beat) <= judgment.bad) res = 5, res2 = 3; FI
		IF (Abs(t - beat) <= judgment.good) res = 4, res2 = 3; FI
		IF (Abs(t - beat) <= judgment.great) res = 3, res2 = 2; FI
		IF (Abs(t - beat) <= judgment.perfect) res = 2, res2 = 1; FI
		IF (Abs(t - beat) <= judgment.perfectPlus) res = 1, res2 = 1; FI
		EntityInput.set(0, res2);
		EntityInput.set(1, t - beat);
		EntityInput.set(3, t - beat);
		IF (res != 0) Play(Clips.Sound, minSFXDistance); FI
		IF (res == 0) SpawnSubJudgeText(Sprites.JudgeMiss); FI
		IF (res == 1) SpawnSubJudgeText(Sprites.JudgePerfectPlus); FI
		IF (res == 2) SpawnSubJudgeText(Sprites.JudgePerfect); FI
		IF (res == 3) SpawnSubJudgeText(Sprites.JudgeGreat); FI
		IF (res == 4) SpawnSubJudgeText(Sprites.JudgeGood); FI
		IF (res == 5) SpawnSubJudgeText(Sprites.JudgeBad); FI
		EntityDespawn.set(0, 1);
		return VOID;
	}
	SonolusApi updateSequential() {
		FUNCBEGIN
		IF (times.now < beat) Return(0); FI
		isHolding = findHoldTouch(lane, enLane) != -1;

		// 判定主代码
		IF (times.now < inputTimeMin) Return(0); FI
		IF (times.now > inputTimeMax) complete(-1); FI
		IF (isHolding == 1) lastHoldTime = Max(lastHoldTime, times.now); FI
		IF (times.now >= beat && lastHoldTime != -1) complete(lastHoldTime); FI
		return VOID;
	}

	SonolusApi updateParallel() {
		FUNCBEGIN
		IF (holdType == 100 || holdType == 101) drawTick(Sprites.TouchTick, beat, lane, enLane); FI
		IF (holdType == 110 || holdType == 111) drawTick(Sprites.TouchScratchTick, beat, lane, enLane); FI
		return VOID;
	}
};
