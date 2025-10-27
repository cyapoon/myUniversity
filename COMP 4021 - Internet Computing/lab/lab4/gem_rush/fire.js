const Fire = function(ctx,x,y){
    // const sequence = { x: 0, y:  160, width: 16, height: 16, count: 8, timing: 200, loop: true };
    const sequence = { x: 0, y:  0, width: 25, height: 25, count: 1, timing: 200, loop: false };



    const sprite = Sprite(ctx,x,y);

    sprite.setSequence(sequence)
        .setScale(2)
        .setShadowScale({ x: 0.75, y: 0.2 })
        .useSheet("wall1.png");

    return {
        getXY: sprite.getXY,
        setXY: sprite.setXY,
        getBoundingBox: sprite.getBoundingBox,
        draw: sprite.draw,
        update: sprite.update
    };
        
}