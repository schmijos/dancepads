// Demo http://jsfiddle.net/X5T64/15/

function HSLToRGB(hsl) {
    var H = hsl.H,
        S = hsl.S,
        L = hsl.L,
        R, G, B, _1, _2;
	function Hue_2_RGB(v1, v2, vH) {
		if (vH < 0) vH += 1;
		if (vH > 1) vH -= 1;
		if ((6 * vH) < 1) return v1 + (v2 - v1) * 6 * vH;
		if ((2 * vH) < 1) return v2;
		if ((3 * vH) < 2) return v1 + (v2 - v1) * ((2 / 3) - vH) * 6;
		return v1;
	}
	if (S == 0) { // HSL from 0 to 1
		R = L * 255;
		G = L * 255;
		B = L * 255;
	} else {
		if (L < 0.5) _2 = L * (1 + S);
		else _2 = (L + S) - (S * L);
		_1 = 2 * L - _2;
		R = 255 * Hue_2_RGB(_1, _2, H + (1 / 3));
		G = 255 * Hue_2_RGB(_1, _2, H);
		B = 255 * Hue_2_RGB(_1, _2, H - (1 / 3));
	}
	return {
		R: Math.round(R),
		G: Math.round(G),
		B: Math.round(B)
	};
};

function generateBasePalette() {
    var tablength = 10;
    var colors = [];
    
    // hsl rainbow, then converted to rgb
    for (var i=0; i<tablength; i++) {
        var h = i/tablength, 
            s = 1, 
            l;
        
        l = 0.35;
        var hsl1 = {H:h,S:s,L:l};
        var rgb1 = HSLToRGB(hsl1);
        colors[3*i] = rgb1;
        
        l = 0.5;
        var hsl2 = {H:h,S:s,L:l};
        var rgb2 = HSLToRGB(hsl2);
        colors[3*i+1] = rgb2;
                         
        l = 0.8;
        var hsl3 = {H:h,S:s,L:l};
        var rgb3 = HSLToRGB(hsl3);
        colors[3*i+2] = rgb3;
    }
    
    // black & white
    var black = {R:0,G:0,B:0};
    var white = {R:255,G:255,B:255};
    colors[30] = black;
    colors[31] = white;
    
    return colors;
}

function addQuad(rgb, to) {
    $(to).append(
        $('<div/>', {
            'class': 'quad',
            'style': 'background-color: rgb('
            +rgb.R+','
            +rgb.G+','
            +rgb.B+');'
        })
    );
}

function findNearest(baseColors, color) {
    var rWeight = 0.8,
        gWeight = 1,
        bWeight = 0.5,
        minDist = Infinity,
        foundColor;
    baseColors.forEach(function(q){
        var dist = Math.pow(
            rWeight * Math.pow(color.R - q.R, 2) 
            + gWeight * Math.pow(color.G - q.G, 2)
            + bWeight * Math.pow(color.B - q.B, 2)
        , 0.5);
        if (dist < minDist) {
            minDist = dist;
            foundColor = q;
        }
    });
    return foundColor;
}

function getBestHAMmatching(source, nearestindex, previous) {
    var candidateRed = {
        R: nearestindex.R,
        G: previous.G,
        B: previous.B
    };
    var candidateGreen = {
        R: previous.R,
        G: nearestindex.G,
        B: previous.B
    };
    var candidateBlue = {
        R: previous.R,
        G: previous.G,
        B: nearestindex.B
    };
    return findNearest([
        nearestindex, candidateRed,
        candidateGreen, candidateBlue
    ], source);
}

function convertToHam7(basePalette, sourceColors) {
    var result = [];
    var previousHamColor = {R:128,G:128,B:128}; // init with cube center
    sourceColors.forEach(function(sourceColor){
        var indexColor = findNearest(basePalette, sourceColor);
        var hamColor = getBestHAMmatching(sourceColor, indexColor, previousHamColor);
        previousHamColor = hamColor;
        result[result.length] = hamColor;
    });
    return result;
}

$( document ).ready(function() {
    var black = {R:0,G:0,B:0};
    var white = {R:255,G:255,B:255};
    
    colors = generateBasePalette();
    colors.forEach(function(el) {
        addQuad(el, "#palette");
    });
    
    // get nearest
    var c1 = {R:150,G:120,B:40};
    addQuad(c1, "#tries");
    var n1 = findNearest(colors, c1);
    addQuad(n1, "#tries");
    addQuad(white, "#tries");
    
    // get nearest
    var c2 = {R:10,G:45,B:130};
    addQuad(c2, "#tries");
    var n2 = findNearest(colors, c2);
    addQuad(n2, "#tries");
    addQuad(white, "#tries");

    // get nearest
    var c3 = {R:10,G:225,B:13};
    addQuad(c3, "#tries");
    var n3 = findNearest(colors, c3);
    addQuad(n3, "#tries");
    addQuad(white, "#tries");
    
    // HAM7 Simulation Red
    var sourceRed = [], sourceGreen = [], sourceBlue = [];
    for (var i=0; i<32; i++) {
        var v = i*8;
        sourceRed[v] = {R:v,G:128,B:0};   // all shades of red
        sourceGreen[v] = {R:0,G:v,B:128}; // all shades of green
        sourceBlue[v] = {R:128,G:0,B:v};  // all shades of blue
    }
    
    sourceRed.forEach(function(c){
        addQuad(c, "#fluid-test-source");
    });
    sourceGreen.forEach(function(c){
        addQuad(c, "#fluid-test-source");
    });
    sourceBlue.forEach(function(c){
        addQuad(c, "#fluid-test-source");
    });
    
    // try to show each source color adequately
    convertToHam7(colors, sourceRed).forEach(function(c){
        addQuad(c, "#fluid-test-result");
    });
    convertToHam7(colors, sourceGreen).forEach(function(c){
        addQuad(c, "#fluid-test-result");
    });
    convertToHam7(colors, sourceBlue).forEach(function(c){
        addQuad(c, "#fluid-test-result");
    });

});

