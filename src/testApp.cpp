#include "testApp.h"


//#define WIDTH 1024
//#define HEIGHT 768
#define USE_TRANSPARENCY false
static bool reload = false;

//--------------------------------------------------------------
void testApp::setup(){
    gui.addTitle("warpper");
    gui.config->toggleHeight = 18;
	gui.config->buttonHeight = 18;
	gui.config->sliderTextHeight = 22;
	gui.config->titleHeight = 18;
	gui.config->fullActiveColor = 0x094c50;
    warpper.setup();
    //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    //glEnable(GL_POLYGON_SMOOTH);
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofHideCursor();
    ofSetBackgroundColor(0);
	ofSetFrameRate(60);
    ofToggleFullscreen();
//    for(int i= 0 ; i < N_SCREEN ; i++)
//    {
//        bz[i].setup(16,"preset"+ofToString(i)+".bin");
//        bz[i].recall();
//            bz[i].inactive();
//        fbo[i].allocate(WIDTH-5, HEIGHT-5);
//    }


	
	Berkelium::init( Berkelium::FileString::empty() );

	browser = new ofxBerkelium(WIDTH*N_SCREEN, HEIGHT, USE_TRANSPARENCY);
	browser->setListener(this);
    //urls.push_back("http://www.tjfdc.com.cn/");
    //urls.push_back("http://www.sosoap.com");
    //urls.push_back("http://nikebetterworld.com/about");
    //urls.push_back("http://www.google.com");
	urls.push_back("http://127.0.0.1/mac");
    //urls.push_back("file://localhost"+ofToDataPath("index.html",true));
    
	browser->getWindow()->navigateTo(urls[0].data(), urls[0].length());
	
	drawLog = false;
    reload = true;
    gui.setDefaultKeys(true);
    
    gui.loadFromXML();
    
	gui.setAutoSave(true);
    bAlignRight = false;
}

//--------------------------------------------------------------
void testApp::update(){
    warpper.update();
//    if(reload)
//    {
//        for(int i = 0 ; i< N_SCREEN ;i++)
//        {
//            bz[i].recall();
//        }
//            reload = false;
//    }
	Berkelium::update();
	warpper.begin();
    ofSetColor(255);
//    for(int i= 0 ; i < N_SCREEN ; i++)
//    {
//        fbo[i].begin();
//        browser->draw(-i*WIDTH, 0);
//        fbo[i].end();
//    }
    browser->draw(0, 0, WIDTH, HEIGHT);
    warpper.end();

}


//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
//	for(int i= 0 ; i < N_SCREEN ; i++)
//    {
//        bz[i].draw(fbo[i].getTextureReference());
//    }
    ofSetColor(255);
    warpper.draw();	
    //browser->draw(0, 0);
	ofPushStyle();
	
	if(drawLog)
	{
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, 180);
		ofRect(10, 10, 600, ofGetHeight()-10);
		ofSetColor(0, 0, 0, 255);
		int y=30;
		for(int i=0; i<log.size(); i++) {
			ofDrawBitmapString(log[i], 20, y);
			y+=16;
		}
		ofDisableAlphaBlending();
        if(browser->status=="") {
            browser->status = "Press right key to load another URL";
        }
        ofSetHexColor(0x000000);
        ofRect(0, ofGetHeight()-25, ofGetWidth(), 25);
        ofSetHexColor(0xFFFFFF);
        ofDrawBitmapString(browser->status, 10, ofGetHeight()-7);
        ostringstream os;
        os << "c: show/hide controls"<<endl
        << "1: active screen 1"<<endl
        << "2: active screen 2"<<endl
        << "0: deactive all screen"<<endl
        <<"a: corner/anchor controls"<<endl
        <<"s: save"<<endl
        <<"d: default"<<endl
        <<"p: preset (last saved)"<<endl
        <<"framerate: " <<ofToString(ofGetFrameRate(),0)<<endl;
        ofSetHexColor(0x000000);
        ofDrawBitmapString(os.str(),10,ofGetHeight()-200);
        ofPopStyle();
	}
	
	
	gui.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(key)
    {
        case '\\':
            bAlignRight =!bAlignRight;
            gui.setAlignRight(bAlignRight);
            break;
        case ' ':
            //gui.isOn();
            if(gui.isOn())
            {
                //   gui.hide();
                ofHideCursor();
            }
            else {
                //gui.show();
                ofShowCursor();
            }
            break;

    }
    warpper.keyPressed(key);    
//    for(int i= 0 ; i < N_SCREEN ; i++)
//    {
//        bz[i].keyPressed(key);
//    }
//    if(!bz[0].getActive() && !bz[1].getActive())
        browser->keyboard(key, true);
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
warpper.keyReleased(key);	
	switch(key) {
//            case '0':
//             bz[0].inactive();
//             if(N_SCREEN>1)bz[1].inactive();
//            ofHideCursor();
//            break;
//        case '1':
//            bz[0].active();
//             if(N_SCREEN>1)bz[1].inactive();
//            ofShowCursor();
//            break;
//        case '2':
//            bz[0].inactive();
//            if(N_SCREEN>1)bz[1].active();
//            ofShowCursor();
//            break;
		case 'f':
			ofToggleFullscreen();
			break;
		case 'l':
			drawLog = !drawLog;
			break;
	}
//	if(N_SCREEN>1)
//    {
//        if(!bz[0].getActive() && !bz[1].getActive())browser->keyboard(key, false);
//    }
//    else {
//        if(!bz[0].getActive() )browser->keyboard(key, false);
//    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
	browser->mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
//	for(int i= 0 ; i < N_SCREEN ; i++)
//    {
//        bz[i].mouseDragged(x, y);
//    }
    warpper.mouseDragged(x, y, button);
    browser->mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	browser->mouseClick(x, y, button, true);
    warpper.mousePressed(x, y, button);    
//    for(int i= 0 ; i < N_SCREEN ; i++)
//    {
//        bz[i].mousePressed(x, y);
//    }

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    warpper.mouseReleased(x, y, button);
	browser->mouseClick(x, y, button, false);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}


#pragma mark CALLBACKS


//--------------------------------------------------------------
void testApp::onAddressBarChanged(string newURL){
	cout << "*** onAddressBarChanged " << newURL << endl;
	log.push_back("*** onAddressBarChanged "+newURL);
}

//--------------------------------------------------------------
void testApp::onStartLoading(string newURL){
	cout << "*** onStartLoading " << newURL << endl;
	log.push_back("*** onStartLoading " +newURL);
}

//--------------------------------------------------------------
void testApp::onLoad(){
	cout << "*** onLoad " << endl;
	log.push_back("*** onLoad ");
}

//--------------------------------------------------------------
void testApp::onCrashedWorker(){
	cout << "*** onCrashedWorker " << endl;
	log.push_back("*** onCrashedWorker ");
}

//--------------------------------------------------------------
void testApp::onCrashedPlugin(wstring pluginName){
	wcout << "*** onCrashedPlugin " << pluginName << endl;
	log.push_back("*** onCrashedPlugin ");
}

//--------------------------------------------------------------
void testApp::onProvisionalLoadError(string url, int errorCode, bool isMainFrame){
	cout << "*** onProvisionalLoadError " << url << ": " << errorCode << (isMainFrame? " (main frame)":"") << endl;
	log.push_back("*** onProvisionalLoadError " );
}

//--------------------------------------------------------------
void testApp::onConsoleMessage(wstring message, wstring sourceId, int line_no){
	wcout << "*** onConsoleMessage " << message << " from " << sourceId << " line " << line_no << endl;
	log.push_back("*** onConsoleMessage " + wstring2string(message));
}

//--------------------------------------------------------------
void testApp::onScriptAlert(wstring message, wstring defaultValue, string url, int flags, bool success, wstring value){
	wcout << "*** onScriptAlert " << message << endl;
	log.push_back("*** onScriptAlert ");
}

//--------------------------------------------------------------
void testApp::onNavigationRequested(string newURL, string referrer, bool isNewWindow, bool &cancelDefaultAction){
	cout << "*** onNavigationRequested " << newURL << " by " << referrer << (isNewWindow?"  (new window)" : " (same window)") << endl;
	log.push_back("*** onNavigationRequested " + newURL);
}

//--------------------------------------------------------------
void testApp::onLoadingStateChanged(bool isLoading){
	cout << "*** onLoadingStateChanged " << (isLoading?"started":"stopped") << std::endl;
	log.push_back("*** onLoadingStateChanged ");
}

//--------------------------------------------------------------
void testApp::onTitleChanged(wstring title){
	wcout << "*** onTitleChanged " << title << endl;
	ofSetWindowTitle(wstring2string(title));
	log.push_back("*** onTitleChanged ");
}

//--------------------------------------------------------------
void testApp::onTooltipChanged(wstring text){
	wcout << "*** onTooltipChanged " << text << endl;
	log.push_back("*** onTooltipChanged ");
}

//--------------------------------------------------------------
void testApp::onCrashed(){
	cout << "*** onCrashed " << endl;
	log.push_back("*** onCrashed ");
}

//--------------------------------------------------------------
void testApp::onUnresponsive(){
	cout << "*** onUnresponsive " << endl;
	log.push_back("*** onUnresponsive ");
}

//--------------------------------------------------------------
void testApp::onResponsive(){
	cout << "*** onResponsive " << endl;
	log.push_back("*** onResponsive ");
}

//--------------------------------------------------------------
void testApp::onShowContextMenu(int mouseX, int mouseY, int mediaType, string linkUrl, string srcUrl, string pageUrl, string frameUrl, wstring selectedText, bool isEditable, int editFlags){
	cout << "*** onShowContextMenu at " << mouseX << "," << mouseY;
	cout << "; type: ";
	switch (mediaType) {
		case Berkelium::ContextMenuEventArgs::MediaTypeImage:
			cout << "image";
			break;
		case Berkelium::ContextMenuEventArgs::MediaTypeVideo:
			cout << "video";
			break;
		case Berkelium::ContextMenuEventArgs::MediaTypeAudio:
			cout << "audio";
			break;
		default:
			cout << "other";
	}
	if (isEditable || editFlags) {
		cout << " (";
		if (isEditable)
			cout << "editable; ";
		if (editFlags & Berkelium::ContextMenuEventArgs::CanUndo)
			cout << "Undo, ";
		if (editFlags & Berkelium::ContextMenuEventArgs::CanRedo)
			cout << "Redo, ";
		if (editFlags & Berkelium::ContextMenuEventArgs::CanCut)
			cout << "Cut, ";
		if (editFlags & Berkelium::ContextMenuEventArgs::CanCopy)
			cout << "Copy, ";
		if (editFlags & Berkelium::ContextMenuEventArgs::CanPaste)
			cout << "Paste, ";
		if (editFlags & Berkelium::ContextMenuEventArgs::CanDelete)
			cout << "Delete, ";
		if (editFlags & Berkelium::ContextMenuEventArgs::CanSelectAll)
			cout << "Select All";
		cout << ")";
	}
	cout << endl;
	if (linkUrl.length())
		cout << "        Link URL: " << linkUrl << endl;
	if (srcUrl.length())
		cout << "        Source URL: " << srcUrl << endl;
	if (pageUrl.length())
		cout << "        Page URL: " << pageUrl << endl;
	if (frameUrl.length())
		cout << "        Frame URL: " << frameUrl << endl;
	if (selectedText.length())
		wcout << "        Selected Text: " << selectedText << endl;
	
	log.push_back("*** onShowContextMenu");
}

//--------------------------------------------------------------
void testApp::onJavascriptCallback(void* replyMsg, string url, wstring funcName, Berkelium::Script::Variant *args, size_t numArgs){
	
	cout << "*** onJavascriptCallback at URL " << url << ", " << (replyMsg?"synchronous":"async") << endl;
	
	wcout << "    Function name: " << funcName << endl;
	for (size_t i = 0; i < numArgs; i++) {
		Berkelium::WideString jsonStr = toJSON(args[i]);
		wcout << L"    Argument " << i << ": ";
		if (args[i].type() == Berkelium::Script::Variant::JSSTRING) {
			wcout << L"(string) " << args[i].toString() << endl;
		} else {
			wcout << jsonStr << endl;
		}
		Berkelium::Script::toJSON_free(jsonStr);
	}
	if (replyMsg) {
		browser->window()->synchronousScriptReturn(replyMsg, numArgs ? args[0] : Berkelium::Script::Variant());
	}
	
	log.push_back("*** onJavascriptCallback at URL " + url);
}

//--------------------------------------------------------------
void testApp::onRunFileChooser(int mode, wstring title, string defaultFile){
	wcout << "*** onRunFileChooser type " << mode << ", title " << title << ":" << endl;
	cout << defaultFile << endl;
	
	browser->window()->filesSelected(NULL);
}

//--------------------------------------------------------------
void testApp::onExternalHost(wstring message, string origin, string target){
	cout << "*** onExternalHost at URL from " << origin << " to " << target << ":" <<endl;
	wcout << message << endl;
}


