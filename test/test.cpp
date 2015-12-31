// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <osgViewer\View>
#include <osgViewer\Viewer>
#include <osgDB\ReadFile>
#include <osg\Point>
#include "..\osgPC\PointCloudProtocal.h"
#include "..\osgPC\DisplayModeNodeVisitor.h"
#include <osgViewer\ViewerEventHandlers>
#include "..\osgPC\SwitchNodeVisitor.h"


using namespace osgGA;

class ColorHandler : public osgGA::GUIEventHandler
{
public:
    ColorHandler(osg::Node* node)
    : _node(node){}

    virtual bool handle(const GUIEventAdapter& ea, GUIActionAdapter& ga)
    {
        if (ea.getEventType() == GUIEventAdapter::KEYDOWN)
        {
            switch (ea.getKey())
            {
            case osgGA::GUIEventAdapter::KEY_T:
                {
                    osgPC::ShareData shareData;
                    shareData.displayMode = osgPC::ShareData::HEIGHT;
                    shareData.minHeight = 13.075;
                    shareData.maxHeight = 31.795;
                    osgPC::PointCloudProtocal& pcp = osgPC::PointCloudProtocalSingleton::Instance();
                    pcp.writeShareBuffer(shareData);
                    osgPC::DisplayModeNodeVisitor dmnv;
                    dmnv.updateShareData();
                    _node->accept(dmnv);
                    //osgPC::PointCloudGeometry* pcg = dynamic_cast<osgPC::PointCloudGeometry*>(_node->asGroup()->getChild(0)->asGeode()->getDrawable(0));
                    break;
                }
			case osgGA::GUIEventAdapter::KEY_P:
				{
					osg::Vec3d color(1.f, 1.f, 0.f);
					osgPC::ShareData shareData;
					shareData.displayMode = osgPC::ShareData::ASSIGNCOLOR;
					shareData.assignColor = color;
					osgPC::PointCloudProtocal& pcp = osgPC::PointCloudProtocalSingleton::Instance();
					pcp.writeShareBuffer(shareData);
					osgPC::DisplayModeNodeVisitor dmnv;
					dmnv.updateShareData();
					_node->accept(dmnv);
					break;
				}
			case osgGA::GUIEventAdapter::KEY_O:
				{
					osgPC::ShareData shareData;
					shareData.displayMode = osgPC::ShareData::INTENSITY;
					shareData.minIntensity = 1;
					shareData.maxIntensity = 2047;
					osgPC::PointCloudProtocal& pcp = osgPC::PointCloudProtocalSingleton::Instance();
					pcp.writeShareBuffer(shareData);
					osgPC::DisplayModeNodeVisitor dmnv;
					dmnv.updateShareData();
					_node->accept(dmnv);
					break;
				}
			case osgGA::GUIEventAdapter::KEY_8:
				{
					osgPC::ShareData shareData;
					shareData.displayMode = osgPC::ShareData::CLASS;
					shareData.switchMode[5] = FALSE;
					shareData.switchMode[1] = false;
					const osgPC::ShareData & sd = shareData;
					osgPC::PointCloudProtocal& pcp = osgPC::PointCloudProtocalSingleton::Instance();
					pcp.writeShareBuffer(shareData);
					osgPC::SwitchNodeVisitor dmnv;
					dmnv.updateShareData();
					_node->accept(dmnv);
					//osgPC::DisplayModeNodeVisitor dmnv;
					//dmnv.updateShareData();
					//_node->accept(dmnv);

					break;
				}
            default:
                break;
            }
            return false;
        }
        else
            return false;
    }

private:
    osg::Node*  _node;

};

int _tmain(int argc, _TCHAR* argv[])
{
    //std::string filename = "E:\\Works\\lidar\\osg\\hd\\cache\\00656.lasdb";
    //std::string filename = "E:\\Works\\lidar\\osg\\hd\\cache\\035.lasdb";
    //std::string filename = "E:\\Works\\lidar\\osg\\testdata3_cache\\cache\\0.lasdb";
    //std::string filename = "E:\\Works\\lidar\\osg\\testdata5_cache\\cache\\0311.lasdb";
    //osgDB::ReaderWriter::ReadResult rs = rw->readNode(filename);
    //osg::Object* obj = rs.getObject();	//getObject�Ƿ���rs�е�_object������û���������ü��������rs�ڴ��ͷź�obj��ָ��ı��ǲ�ȷ��������
    //osg::Object* obj = rs.takeObject();		//ȡ��rs�е�_object���������ü���������rs�е�_object��ֵΪNULL���ټ���һ�����ü�����unref_nodelete��
    //osg::Geode* geode = dynamic_cast<osg::Geode*>(obj);	//ͨ�����ַ�ʽ��õĽڵ㣬setSceneDataʱ���������޷�ֱ����getNode�õ��ڵ�
    osgViewer::Viewer viewer;
    osg::Group* group = new osg::Group;
    //group->addChild(osgDB::readNodeFile("E:\\Works\\lidar\\osg\\hd\\cache\\00656.lasdb"));
    //osg::Node* geode = osgDB::readNodeFile("E:\\Dev\\Labs\\Point2Model��װ��\\data\\tt_c2\\cache\\0.lasdb");
	osg::Node* geode = osgDB::readNodeFile("E:\\result_cache\\cache\\07507.lasdb");
    group->addChild(geode);
    group->getOrCreateStateSet()->setAttributeAndModes(new osg::Point(1.f), osg::StateAttribute::ON);
    osg::Light* light = new osg::Light;
    light->setAmbient(osg::Vec4(0.f, 0.f, 0.f, 1.f));
    group->getOrCreateStateSet()->setAttributeAndModes(light, osg::StateAttribute::ON);
	viewer.getDatabasePager()->registerPagedLODs(geode);
    viewer.setSceneData(group);
	//viewer.addEventHandler(new osgViewer::WindowSizeHandler);

	viewer.setUpViewInWindow(100, 100, 800, 600);
	//viewer.getEventQueue()->windowResize(100, 100, 400, 300); //û������
	viewer.addEventHandler(new osgViewer::StatsHandler);

    viewer.realize();



    osgPC::PointCloudProtocal& pcp = osgPC::PointCloudProtocalSingleton::Instance();
    bool rs = pcp.createShareBuffer();


	/*osgPC::ShareData shareData;
	shareData.displayMode = osgPC::ShareData::HEIGHT;
	shareData.minHeight = -63.227;
	shareData.maxHeight = 378.997;
	pcp.writeShareBuffer(shareData);
	osgPC::DisplayModeNodeVisitor dmnv;
	dmnv.updateShareData();
	group->accept(dmnv);
	osgPC::PointCloudGeometry* pcg = dynamic_cast<osgPC::PointCloudGeometry*>(group->asGroup()->getChild(0)->asGeode()->getDrawable(0));*/
	std::vector<int > a(5);
	rs = (a.size() - 1) <= -6 ;


    viewer.addEventHandler(new ColorHandler(group));
    viewer.run();

	return 0;
}

