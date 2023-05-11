import {Engine} from "./Engine.js";
import {PBRShader} from "../GL Helpers/ShaderHandler.js";
import {loadGLTF} from "../GL Helpers/AssetLoader.js";
import {FirstPersonController} from "./FirstPersonController.js";
import {SceneGraph} from "./SceneGraph.js";

window.onload = async function () {
    let scenario = document.cookie.split("; ").find((row) => row.startsWith("pathToDemo="))?.split("=")[1] || sessionStorage.getItem("pathToDemo")
    console.log(scenario);
    console.log("test");
    let data = await loadGLTF(scenario || "Scenario1");
    let scene = SceneGraph.fromGLTF(data, PBRShader);

    const nonEuclideanParadise = new Engine(PBRShader, scene, 1440);
    nonEuclideanParadise.start();

    let player = new FirstPersonController(nonEuclideanParadise.activeScene.mainCamera.transform, 0.015);
    window.addEventListener(nonEuclideanParadise.update.type, () => player.move());
}

canvas.onclick = function() {
    canvas.requestPointerLock();
    canvas.requestFullscreen().catch((err) => {
        alert(`Error attempting to enable fullscreen mode: ${err.message} (${err.name})`);
    });
};
