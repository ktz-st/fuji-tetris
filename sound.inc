{$IFDEF STE}
{$L dmasound.o}
{$i msx/sfx.inc}

function IsSteMachine: byte; external;
procedure DmaSoundInit; external;
procedure DmaSoundDone; external;
procedure DmaPlayRaw(sample: pointer; length: cardinal); external;

procedure InitSound;
begin
    soundReady := false;
    sfxDrop := @DROP_RAW_DATA[0];
    sfxRotate := @ROTATE_RAW_DATA[0];
    sfxShake[1] := @SHAKE1_RAW_DATA[0];
    sfxShake[2] := @SHAKE2_RAW_DATA[0];
    sfxShake[3] := @SHAKE3_RAW_DATA[0];
    sfxShake[4] := @SHAKE4_RAW_DATA[0];
    sfxDropLen := SizeOf(DROP_RAW_DATA);
    sfxRotateLen := SizeOf(ROTATE_RAW_DATA);
    sfxShakeLen[1] := SizeOf(SHAKE1_RAW_DATA);
    sfxShakeLen[2] := SizeOf(SHAKE2_RAW_DATA);
    sfxShakeLen[3] := SizeOf(SHAKE3_RAW_DATA);
    sfxShakeLen[4] := SizeOf(SHAKE4_RAW_DATA);
    steMachine := IsSteMachine <> 0;

    if not steMachine then
        exit;

    DmaSoundInit;
    soundReady := true;
end;

procedure DoneSound;
begin
    if steMachine then
        DmaSoundDone;
    soundReady := false;
end;

procedure PlayDropSound;
begin
    if soundReady and (sfxDrop <> nil) then
        DmaPlayRaw(sfxDrop, sfxDropLen);
end;

procedure PlayRotateSound;
begin
    if soundReady and (sfxRotate <> nil) then
        DmaPlayRaw(sfxRotate, sfxRotateLen);
end;

procedure PlayShakeSound(level: byte);
begin
    if level < 1 then
        level := 1;
    if level > 4 then
        level := 4;
    if soundReady and (sfxShake[level] <> nil) then
        DmaPlayRaw(sfxShake[level], sfxShakeLen[level]);
end;
{$ELSE}
procedure InitSound;
begin
end;

procedure DoneSound;
begin
end;

procedure PlayDropSound;
begin
end;

procedure PlayRotateSound;
begin
end;

procedure PlayShakeSound(level: byte);
begin
    if level = 0 then
        exit;
end;
{$ENDIF}
