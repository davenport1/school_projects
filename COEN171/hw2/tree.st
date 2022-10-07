Object subclass: #Node
    instanceVariableNames: 'data left right'
    classVaribleNames: ''
    poolDictionaries: ''    

!Node methodsFor: 'initialization'!
data: anObject
    data := anObject
!!

!Node methodsFor: 'manipulation'!
insert: anObject
    anObject < data
        ifTrue: 
            [ left = nil 
                ifTrue: [left := Node new data: anObject]
                ifFalse: [left insert: anObject]].
    anObject > data
        ifTrue: 
            [ right = nil
                ifTrue: [right := Node new data: anObject]
                ifFalse: [right insert: anObject]].
!
member: anObject
    anObject < data
        ifTrue: [
            left = nil
                ifTrue: [^false]
                ifFalse: [^left member: anObject]].
    anObject > data
        ifTrue: [
            right = nil
                ifTrue: [^false]
                ifFalse: [^right member: anobject]].
    ^true.
!!

Object subcass: #Tree
    instanceVariableNames: 'root'
    classVaribleNames: ''
    poolDictionaries: ''!

!Tree methodsFor: 'manipulation'
insert: anObject
    root = nil
        ifTrue: [root := Node new data: anObject ]
        ifFalse: [root insert: anObject].
!

member: anObject 
    root = nil
        ifTrue: [^false]
        ifFalse: [^root member: anObject ].
!!
