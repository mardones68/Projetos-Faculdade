const canvas = document.getElementById("glcanvas");
const gl = canvas.getContext("webgl");

// Vertex Shader
const vertexShaderSource = `
  attribute vec2 aPosition;
  uniform mat3 uMatrix;
  void main() {
    vec3 pos = uMatrix * vec3(aPosition, 1.0);
    gl_Position = vec4(pos.xy, 0.0, 1.0);
  }
`;

// Fragment Shader
const fragmentShaderSource = `
  precision mediump float;
  void main() {
    gl_FragColor = vec4(0.2, 0.6, 0.9, 1.0);
  }
`;

function compileShader(src, type) {
  const shader = gl.createShader(type);
  gl.shaderSource(shader, src);
  gl.compileShader(shader);
  return shader;
}

const vertexShader = compileShader(vertexShaderSource, gl.VERTEX_SHADER);
const fragmentShader = compileShader(fragmentShaderSource, gl.FRAGMENT_SHADER);

// Link programa
const program = gl.createProgram();
gl.attachShader(program, vertexShader);
gl.attachShader(program, fragmentShader);
gl.linkProgram(program);
gl.useProgram(program);

// Define um quadrado centrado na origem
const vertices = new Float32Array([
  -0.3, -0.3,
   0.3, -0.3,
   0.3,  0.3,
  -0.3, -0.3,
   0.3,  0.3,
  -0.3,  0.3
]);

const buffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

const aPosition = gl.getAttribLocation(program, "aPosition");
gl.enableVertexAttribArray(aPosition);
gl.vertexAttribPointer(aPosition, 2, gl.FLOAT, false, 0, 0);

const uMatrix = gl.getUniformLocation(program, "uMatrix");

function drawScene(time) {
  gl.clearColor(1, 1, 1, 1);
  gl.clear(gl.COLOR_BUFFER_BIT);

  const angle = time * 0.001; // tempo em segundos

  const cos = Math.cos(angle);
  const sin = Math.sin(angle);

  const rotationMatrix = new Float32Array([
     cos, sin, 0,
    -sin, cos, 0,
       0,   0, 1
  ]);

  gl.uniformMatrix3fv(uMatrix, false, rotationMatrix);

  gl.drawArrays(gl.TRIANGLES, 0, 6);

  requestAnimationFrame(drawScene);
}

requestAnimationFrame(drawScene);
