module.exports = [
    { // 0
        name: 'Plain',
        fg: BLACK,
        tile: 0,
        solid: 0,
        desc: 'Nothing of interest here'
    },
    { // 1
        name: 'Grass',
        fg: GREEN,
        tile: 5,
        solid: false,
        desc: 'The soft, cool blades of grass brush against your ankles as you walk.'
    },
    { // 2
        name: 'Rock',
        fg: GREY,
        tile: 103,
        solid: false,
        desc: 'You find yourself facing a field of massive, imposing boulders, each one seeming more insurmountable than the last.'
    },
    { // 3
        name: 'Oak',
        fg: DARK_GREEN,
        tile: 54,
        solid: true,
        desc: 'You encounter a thick grove of oak trees, their gnarled trunks blocking your path.'
    },
    { // 4
        name: 'Shallow Water',
        fg: AQUA,
        bg: BLUE,
        tile: 574,
        solid: false,
        desc: 'The waves gently touch your feet as you enter the shallow water'
    },
    { // 5
        name: 'Deep Water',
        bg: BLUE,
        tile: 0,
        solid: true,
        desc: 'The ocean stops you from venturing any further'
    }
]