procedure ShufflePool;
var
    r, s, tmp: byte;
begin
    // Wypełnij pulę kolejnymi typami klocków: 0..6
    for r := 0 to 6 do tilepool[r] := r;

    // Fisher-Yates: tasuj od końca do początku
    for r := 6 downto 1 do begin
        s := Random(r + 1);     // losuj indeks z zakresu 0..r (włącznie)
        // zamień tilepool[r] z tilepool[s]
        tmp := tilepool[r];
        tilepool[r] := tilepool[s];
        tilepool[s] := tmp;
    end;

    poolsize := 7;
end;

function TossTile:byte;
begin
    if poolsize = 0 then ShufflePool;
    dec(poolsize);
    TossTile:=tilepool[poolsize];
    inc(stats[TossTile]);
end;