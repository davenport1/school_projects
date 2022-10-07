program bst(input, output);

    {$mode objfpc}

    type
    tree = ^node;
    node = record
        info : integer;
        left : tree;
        right : tree
    end;

    var t : tree;
    var x :     integer;

    function insert(root : tree; value : integer) : tree;
    begin
    if root = nil then
    begin
        new(root);
        root^.left := nil;
        root^.right := nil;
        root^.info := value;
    end
    else if root^.info < value then
    begin
        root^.right := insert(root^.right, value);
    end
        else if root^.info > value then
    begin
        root^.left := insert(root^.left, value);
    end;
    insert := root;

    end;

    function member(root : tree; value : integer) : boolean; 
    begin
    if root = nil then Result := false;
    if value < root^.info then member(root^.left, value);
    if value > root^.info then member(root^.right, value);
    Result := true;
    end;


begin
    t := nil;
    readln(x);

    while x <> -1 do begin 
    t := insert(t,x);
    readln(x);
    end;
    
    readln(x);

    while x <> -1 do begin
    if member(t,x) = true then writeln('true') else writeln('false');
    readln(x);
    end;

end.
