#include "AnimationLoader.h"

bool AnimationLoader::LoadAnimation(const std::string &csaFile) {
    std::ifstream file(csaFile);

    if (!file.is_open()){
        std::cerr << "Failed to open file: " << csaFile << std::endl;
        return false;
    }

    std::string csaContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    yyjson_doc* doc = yyjson_read(csaContent.c_str(), csaContent.size(), 0);
    if (!doc){
        std::cerr << "Failed to parse CSA file as JSON: " << csaFile << std::endl;
        return false;
    }

    yyjson_val* root = yyjson_doc_get_root(doc);

    // Información de la textura
    yyjson_val* textureAtlas = yyjson_obj_get(root, "textureAtlas");
    if (!textureAtlas) {
        std::cerr << "Error: 'textureAtlas' not found in the CSA file" << std::endl;
        yyjson_doc_free(doc);
        return false;
    }

    texturePath  = yyjson_get_str(yyjson_obj_get(textureAtlas, "texturePath"));
    regionWidth  = yyjson_get_int(yyjson_obj_get(textureAtlas, "regionWidth"));
    regionHeight = yyjson_get_int(yyjson_obj_get(textureAtlas, "regionHeight"));

    // Ciclos de animación
    std::string jsonFile = yyjson_get_str(yyjson_obj_get(root, "jsonFile"));
    if (!LoadJson(jsonFile)){
        std::cerr << "Failed to load JSON file: " << jsonFile << std::endl;
        yyjson_doc_free(doc);
        return false;
    }

    yyjson_val* cycles = yyjson_obj_get(root, "cycles");
    if (!cycles) {
        std::cerr << "Error: 'cycles' not found in the CSA file" << std::endl;
        yyjson_doc_free(doc);
        return false;
    }

    yyjson_val* cycleIt;
    yyjson_obj_iter iter;

    yyjson_obj_iter_init(cycles, &iter);
    while ((cycleIt = yyjson_obj_iter_next(&iter))){
        std::string cycleName = yyjson_get_str(cycleIt);
        yyjson_val* cycleData = yyjson_obj_get(cycles, cycleName.c_str());
        AnimationCycle cycle;
        cycle.frameDuration = yyjson_get_real(yyjson_obj_get(cycleData, "frameDuration"));
        cycle.isLooping = yyjson_get_bool(yyjson_obj_get(cycleData, "isLooping"));

        yyjson_val* framesArray = yyjson_obj_get(cycleData, "frames");
        if (!framesArray) {
            std::cerr << "Error: 'frames' array not found for cycle: " << cycleName << std::endl;
            continue;
        }

        // Aquí se deben obtener los frames directamente en el ciclo actual
        size_t frameCount = yyjson_arr_size(framesArray);
        for (size_t i = 0; i < frameCount; ++i){
            int frameIdx = yyjson_get_int(yyjson_arr_get(framesArray, i));

            if (frameIdx >= frameDataList.size()) {
                std::cerr << "Invalid frame index for cycle: " << cycleName << std::endl;
                continue;
            }

            // Accedemos a los datos del frame desde el JSON cargado
            FrameData frame = frameDataList[frameIdx];  // Asegúrate de que `frameDataList` esté cargado correctamente
            cycle.frames.push_back(frame);
        }

        animationCycles[cycleName] = cycle;
    }

    yyjson_doc_free(doc);

    return true;
}

bool AnimationLoader::LoadJson(const std::string &jsonFile) {
    std::ifstream file(jsonFile);
    if (!file.is_open()){
        std::cerr << "Failed to open file: " << jsonFile << std::endl;
        return false;
    }

    std::string jsonContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    yyjson_doc* doc = yyjson_read(jsonContent.c_str(), jsonContent.size(), 0);
    if (!doc){
        std::cerr << "Failed to parse JSON file: " << jsonFile << std::endl;
        return false;
    }

    yyjson_val* root = yyjson_doc_get_root(doc);
    yyjson_val* frames = yyjson_obj_get(root, "frames");

    size_t frameCount = yyjson_arr_size(frames);
    for (size_t i = 0; i < frameCount; ++i){
        yyjson_val* frame = yyjson_arr_get(frames, i);

        FrameData frameData;
        yyjson_val* frameVal = yyjson_obj_get(frame, "frame");
        frameData.x = yyjson_get_int(yyjson_obj_get(frameVal, "x"));
        frameData.y = yyjson_get_int(yyjson_obj_get(frameVal, "y"));
        frameData.width = yyjson_get_int(yyjson_obj_get(frameVal, "width"));
        frameData.height = yyjson_get_int(yyjson_obj_get(frameVal, "height"));

        frameDataList.push_back(frameData);  // Guarda los frames en `frameDataList`
    }

    yyjson_doc_free(doc);

    return true;
}

AnimationCycle AnimationLoader::GetAnimationCycle(const std::string& cycleName) const{
    if (animationCycles.find(cycleName) != animationCycles.end()){
        return animationCycles.at(cycleName);
    }

    return {};
}